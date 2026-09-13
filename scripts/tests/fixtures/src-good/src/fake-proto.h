/*@audit factory Fake\FakeQueue FakeMaker::newFakeQueue */

/*@zep Fake\FakeQueue commitThing(int handle) -> void */
void mtl_fakequeue_commit_thing(zval *handle);
/*@zep Fake\FakeQueue waitForThing(int handle) -> void */
void mtl_fakequeue_wait_for_thing(zval *handle);
/*@zep Fake\FakeQueue makeChild(int handle) -> int */
zend_long mtl_fakequeue_make_child(zval *handle);
/*@zep Fake\FakeQueue depth(int handle) -> int */
zend_long mtl_fakequeue_depth(zval *handle);

/*@zep Fake\FakeMaker newFakeQueue(int handle) -> int */
zend_long mtl_fakemaker_new_fake_queue(zval *handle);
/*@zep-construct Fake\FakeMaker init() -> int */
zend_long mtl_fakemaker_init(void);
/*@audit partial Fake\FakeMaker slice-zero fixture */
