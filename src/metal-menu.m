#import <AppKit/AppKit.h>
#import "metal-menu.h"
#import "metal-app.h"

static NSString *mtl_pending_action = nil;

@interface MTLMenuTarget : NSObject
- (void)handleCustomAction:(id)sender;
- (void)handleQuit:(id)sender;
@end

@implementation MTLMenuTarget
- (void)handleCustomAction:(id)sender
{
    NSMenuItem *item = (NSMenuItem *)sender;
    if ([item.representedObject isKindOfClass:[NSString class]]) {
        mtl_pending_action = [item.representedObject copy];
    }
}

- (void)handleQuit:(id)sender
{
    (void)sender;
    mtl_pending_action = @"quit";
    mtl_app_terminate();
}
@end

static MTLMenuTarget *mtl_menu_target = nil;

static NSMenuItem *mtl_find_top_menu(NSString *title)
{
    NSMenu *mainMenu = NSApp.mainMenu;
    if (!mainMenu) {
        return nil;
    }
    for (NSMenuItem *item in mainMenu.itemArray) {
        if ([item.title isEqualToString:title]) {
            return item;
        }
    }
    return nil;
}

int mtl_menu_install_default(const char *app_name)
{
    if (!mtl_app_init()) {
        return 0;
    }

    @autoreleasepool {
        if (!mtl_menu_target) {
            mtl_menu_target = [MTLMenuTarget new];
        }

        NSString *name = app_name && app_name[0]
            ? [NSString stringWithUTF8String:app_name]
            : @"Metal";

        NSMenu *mainMenu = [NSMenu new];

        // Application menu
        NSMenu *appMenu = [NSMenu new];
        NSMenuItem *about = [[NSMenuItem alloc] initWithTitle:[NSString stringWithFormat:@"About %@", name]
                                                       action:nil
                                                keyEquivalent:@""];
        [appMenu addItem:about];
        [appMenu addItem:[NSMenuItem separatorItem]];
        NSMenuItem *quit = [[NSMenuItem alloc] initWithTitle:[NSString stringWithFormat:@"Quit %@", name]
                                                      action:@selector(handleQuit:)
                                               keyEquivalent:@"q"];
        quit.target = mtl_menu_target;
        quit.representedObject = @"quit";
        [appMenu addItem:quit];

        NSMenuItem *appMenuItem = [NSMenuItem new];
        appMenuItem.submenu = appMenu;
        [mainMenu addItem:appMenuItem];

        // File
        NSMenu *fileMenu = [[NSMenu alloc] initWithTitle:@"File"];
        NSMenuItem *fileItem = [[NSMenuItem alloc] initWithTitle:@"File" action:nil keyEquivalent:@""];
        fileItem.submenu = fileMenu;
        [mainMenu addItem:fileItem];

        // Edit
        NSMenu *editMenu = [[NSMenu alloc] initWithTitle:@"Edit"];
        NSMenuItem *editItem = [[NSMenuItem alloc] initWithTitle:@"Edit" action:nil keyEquivalent:@""];
        editItem.submenu = editMenu;
        [mainMenu addItem:editItem];

        // Window
        NSMenu *windowMenu = [[NSMenu alloc] initWithTitle:@"Window"];
        NSMenuItem *minimize = [[NSMenuItem alloc] initWithTitle:@"Minimize"
                                                          action:@selector(performMiniaturize:)
                                                   keyEquivalent:@"m"];
        [windowMenu addItem:minimize];
        NSMenuItem *windowItem = [[NSMenuItem alloc] initWithTitle:@"Window" action:nil keyEquivalent:@""];
        windowItem.submenu = windowMenu;
        [mainMenu addItem:windowItem];
        [NSApp setWindowsMenu:windowMenu];

        // Help
        NSMenu *helpMenu = [[NSMenu alloc] initWithTitle:@"Help"];
        NSMenuItem *helpItem = [[NSMenuItem alloc] initWithTitle:@"Help" action:nil keyEquivalent:@""];
        helpItem.submenu = helpMenu;
        [mainMenu addItem:helpItem];

        [NSApp setMainMenu:mainMenu];
        return 1;
    }
}

int mtl_menu_add_item(
    const char *menu_title,
    const char *item_title,
    const char *key_equivalent,
    const char *action_id
) {
    if (!menu_title || !item_title || !action_id) {
        return 0;
    }
    if (!mtl_app_init()) {
        return 0;
    }
    if (!NSApp.mainMenu) {
        mtl_menu_install_default("Metal");
    }

    @autoreleasepool {
        if (!mtl_menu_target) {
            mtl_menu_target = [MTLMenuTarget new];
        }

        NSString *menuTitle = [NSString stringWithUTF8String:menu_title];
        NSString *itemTitle = [NSString stringWithUTF8String:item_title];
        NSString *key = key_equivalent ? [NSString stringWithUTF8String:key_equivalent] : @"";
        NSString *action = [NSString stringWithUTF8String:action_id];

        NSMenuItem *top = mtl_find_top_menu(menuTitle);
        if (!top) {
            NSMenu *submenu = [[NSMenu alloc] initWithTitle:menuTitle];
            top = [[NSMenuItem alloc] initWithTitle:menuTitle action:nil keyEquivalent:@""];
            top.submenu = submenu;
            [NSApp.mainMenu addItem:top];
        }

        NSMenuItem *item = [[NSMenuItem alloc] initWithTitle:itemTitle
                                                      action:@selector(handleCustomAction:)
                                               keyEquivalent:key];
        item.target = mtl_menu_target;
        item.representedObject = action;

        // Quit convenience: wire terminate as well when action_id is "quit"
        if ([action isEqualToString:@"quit"]) {
            item.action = @selector(handleQuit:);
        }

        [top.submenu addItem:item];
        return 1;
    }
}

int mtl_menu_poll_action(char *out_action, int out_action_len)
{
    if (!out_action || out_action_len <= 0) {
        return 0;
    }
    out_action[0] = '\0';

    if (!mtl_pending_action) {
        return 0;
    }

    @autoreleasepool {
        BOOL ok = [mtl_pending_action getCString:out_action
                                       maxLength:(NSUInteger)out_action_len
                                        encoding:NSUTF8StringEncoding];
        mtl_pending_action = nil;
        return ok ? 1 : 0;
    }
}
