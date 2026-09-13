#import <Foundation/Foundation.h>

// Regression fixture (Task 2 fix-round): real Metal headers put bare
// forward declarations, naming OTHER types, immediately before the real
// @protocol block (see MTLCommandQueue.h: `@protocol MTLDevice;`,
// `@protocol MTLCommandBuffer;`, `@protocol MTLResidencySet;` right before
// `@protocol MTLCommandQueue <NSObject> ... @end`). This is the case that
// actually corrupts parsing: the mismatched-name forward decl is treated
// as a block opener, closed at the next literal `@end` (the real
// FakeQueue's), discarded for the name mismatch, and the parse offset is
// left past the real block — so FakeQueue is never matched at all.
@protocol FakeDevice;
@protocol FakeChild, FakeSibling;

@protocol FakeQueue <NSObject>
- (void)commitThing;
- (void)waitForThing;
- (id)makeChild;
@property (readonly) NSUInteger depth;
@end

// `@class` forward decls are the legal ObjC form for @interface (there is
// no `@interface X;` forward-decl syntax); confirm one immediately before
// the real @interface block doesn't confuse classBlocks() either.
@class FakeMaker;

@interface FakeMaker : NSObject
- (id<FakeQueue>)newFakeQueue;
@end
