#import <Foundation/Foundation.h>

// Regression fixture (Wave A): a header that only *forward-declares* the
// audited protocol, and that sorts before its real home (FakeProto.h) in
// the directory scan. Real Metal headers do exactly this — MTLFunction is
// forward-declared in MTLComputeCommandEncoder.h, MTLRenderPipelineState
// and MTLSamplerState in MTLArgumentEncoder.h, MTLRenderCommandEncoder in
// MTLCommandBuffer.h — all of which sort before the header that actually
// declares them. Resolving a companion class to a header like this one
// audits it against zero members, so sdkHeaderFor() must keep looking
// until it finds a real block.
@protocol FakeQueue;
@class FakeMaker;
