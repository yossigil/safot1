#import  <iostream>
#import  "gtest/gtest.h"
#import  "a-list.h"
#import  "test.h"

// Mark here every exceptions that was tested;
// Add test that all exceptions were checked.
// Add tests that error strings are meaningful; consult with Yossi on how

/**
 * Tests of mini-lisp basics; should be renamed one day
 */

#define EXPECT_STRUE(e) EXPECT_TRUE(e.t())
#define EXPECT_SFALSE(e) EXPECT_TRUE(e.null())
using Engine::lookup, Engine::set;

TEST(Lookup, T0) {
  CAREFULLY_EXPECT(EQ,lookup("T"),"T", << 2); 
}

TEST(Lookup, T) {
  EXPECT_STRUE(lookup("T"));
  EXPECT_TRUE(lookup("T").eq(T));
}

TEST(Lookup, NIL) {
  EXPECT_SFALSE(lookup("NIL"));
  EXPECT_FALSE(lookup("NIL").t());
  EXPECT_TRUE(lookup("NIL").eq("NIL"));
  EXPECT_TRUE(lookup("NIL").null());
}

TEST(Lookup, Failuer1) {
  EXPECT_EXCEPTION(lookup("bar baz"),S("bar baz"), UNDEFINED_ATOM);
}

TEST(Lookup, Failure2) {
  EXPECT_EXCEPTION(lookup("foo" "bar" "baz"), S("foo" "bar" "baz"), UNDEFINED_ATOM);
}

TEST(Lookup, Failure3) {
  EXPECT_EXCEPTION(lookup(" Y "), S(" Y "), UNDEFINED_ATOM);
}

TEST(Lookup, Failure4) {
  EXPECT_EXCEPTION(lookup("foo"), S("foo"), UNDEFINED_ATOM);
}

TEST(Lookup, Failure5) {
  S y("Y a b c");
  EXPECT_EXCEPTION(lookup(y), y, UNDEFINED_ATOM);
}


TEST(Lookup, SetGoodLookup) {
  Engine::set("X","Y");
  EXPECT_STRUE(lookup("X"));
}

TEST(Lookup, TeaAndCofee) {
  Engine::set("coffee","tea");
  EXPECT_EQ(lookup("coffee"), S("tea"));
  EXPECT_EXCEPTION(lookup("tea"),S("tea"), UNDEFINED_ATOM);
  Engine::set("tea","coffee");
  EXPECT_STRUE(lookup("tea"));
  EXPECT_STRUE(lookup("coffee"));
  EXPECT_EQ(lookup("tea"), S("coffee"));
}
