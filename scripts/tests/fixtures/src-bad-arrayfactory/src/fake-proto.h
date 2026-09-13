/*
 * Negative fixture (Wave A review): the factory marker names a producer
 * that returns `array`, but whose selector is NOT the sanctioned NSError**
 * pattern — it is a plain list (the real-world shape of
 * MTLLibrary::functionNames). Before the narrowing, any array-returning
 * producer satisfied a construction path, so a marker like this passed
 * silently. It must now hard-fail.
 */

/*@audit factory Fake\FakeQueue FakeMaker::queueNames */

/*@zep Fake\FakeQueue commitThing(int handle) -> void */
void mtl_fakequeue_commit_thing(zval *handle);
/*@zep Fake\FakeQueue waitForThing(int handle) -> void */
void mtl_fakequeue_wait_for_thing(zval *handle);
/*@zep Fake\FakeQueue makeChild(int handle) -> int */
zend_long mtl_fakequeue_make_child(zval *handle);
/*@zep Fake\FakeQueue depth(int handle) -> int */
zend_long mtl_fakequeue_depth(zval *handle);

/*@zep Fake\FakeMaker queueNames(int handle) -> array */
void mtl_fakemaker_queue_names(zval *return_value, zval *handle);
/*@zep-construct Fake\FakeMaker init() -> int */
zend_long mtl_fakemaker_init(void);
/*@audit partial Fake\FakeMaker array-factory fixture */
