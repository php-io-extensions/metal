/*
 * Positive fixture (Wave A review): the factory marker names an
 * NSError**-pattern producer — selector ends in `Error`, return shape is
 * the {handle, error} array. That still yields the class's handle, so it
 * must satisfy the construction path (this is how MTLLibrary and
 * MTLRenderPipelineState are constructed at all).
 */

/*@audit factory Fake\FakeQueue FakeMaker::newFakeQueueError */

/*@zep Fake\FakeQueue commitThing(int handle) -> void */
void mtl_fakequeue_commit_thing(zval *handle);
/*@zep Fake\FakeQueue waitForThing(int handle) -> void */
void mtl_fakequeue_wait_for_thing(zval *handle);
/*@zep Fake\FakeQueue makeChild(int handle) -> int */
zend_long mtl_fakequeue_make_child(zval *handle);
/*@zep Fake\FakeQueue depth(int handle) -> int */
zend_long mtl_fakequeue_depth(zval *handle);

/*@zep Fake\FakeMaker newFakeQueueError(int handle) -> array */
void mtl_fakemaker_new_fake_queue_error(zval *return_value, zval *handle);
/*@zep-construct Fake\FakeMaker init() -> int */
zend_long mtl_fakemaker_init(void);
/*@audit partial Fake\FakeMaker error-factory fixture */
