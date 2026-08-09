<?php

declare(strict_types=1);

/**
 * Metal demo: open a window, clear-animate a color, Quit via menu (Cmd+Q or Demo → Quit Demo).
 *
 *   php -d extension=./ext/modules/metal.so examples/proof_window.php
 */

use Metal\MTL\App;
use Metal\MTL\Device;
use Metal\MTL\Menu;
use Metal\MTL\Window;

if (!extension_loaded('metal')) {
    fwrite(STDERR, "metal extension not loaded\n");
    exit(1);
}

App::init();
App::resetQuit();

Menu::installDefault('Metal Demo');
Menu::addItem('Demo', 'Quit Demo', 'q', 'quit');

$window = Window::create('php-io-extensions/metal', 960, 540);
if ($window === 0) {
    fwrite(STDERR, "failed to create window\n");
    exit(1);
}

$device = Device::createSystemDefault();
if ($device === 0) {
    fwrite(STDERR, "no Metal device\n");
    exit(1);
}

if (!Window::attachDevice($window, $device)) {
    fwrite(STDERR, "failed to attach Metal device to window\n");
    exit(1);
}

echo 'Metal device: ' . Device::getName($device) . PHP_EOL;
echo "Close the window or use Demo → Quit Demo (Cmd+Q) to exit.\n";

$maxFrames = getenv('METAL_DEMO_MAX_FRAMES');
$maxFrames = $maxFrames === false || $maxFrames === '' ? null : max(1, (int) $maxFrames);

$frame = 0;
while (!Window::shouldClose($window) && !App::shouldQuit()) {
    App::poll();

    $action = Menu::pollAction();
    if ($action === 'quit') {
        break;
    }

    // Slow RGB pulse so "something rendered" is obvious.
    $t = $frame / 60.0;
    $r = (int) (128 + 127 * sin($t));
    $g = (int) (128 + 127 * sin($t + 2.094));
    $b = (int) (128 + 127 * sin($t + 4.188));
    Window::clear($window, $r, $g, $b, 255);

    $frame++;
    if (!is_null($maxFrames) && $frame >= $maxFrames) {
        break;
    }
    usleep(16_000);
}

Window::destroy($window);
Device::release($device);

echo "demo exited cleanly\n";
