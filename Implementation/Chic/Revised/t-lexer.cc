#import  <gtest/gtest.h>
#import  "lexer.h"

static void t(const char *s) {
  lexer::initialize(strdup(s));
}

using lexer::next;
using lexer::$;

#include "layout.h"
static const char* nextS() {
  Short h = next();
  return A + h;
}

#import  "Testee.h"
#import  <string.h>

TEST(lexer, ListTokenizationWithGet) {
  lexer::initialize(strdup("(a)"));
  Short token = lexer::get();
  EXPECT_EQ(token, '(');
  EXPECT_STREQ("A", nextS());
  EXPECT_EQ(')', lexer::get());
  EXPECT_EQ($, lexer::get());
}

TEST(lexer, ListTokenizationTwice) {
  {
    lexer::initialize(strdup("(a)"));
    Short token = lexer::get();
    EXPECT_EQ(token, '(');
    EXPECT_STREQ("A", nextS());
    EXPECT_EQ(')', lexer::get());
    EXPECT_EQ($, lexer::get());
  }
  {
    lexer::initialize(strdup("(a)"));
    Short token = lexer::get();
    EXPECT_EQ(token, '(');
    EXPECT_STREQ("A", nextS());
    EXPECT_EQ(')', lexer::get());
    EXPECT_EQ($, lexer::get());
  }
}

TEST(lexer, ListTokenizationThrice) {
  {
    lexer::initialize(strdup("(a)"));
    Short token;
    token = lexer::get();
    EXPECT_EQ(token, '(');
    EXPECT_STREQ("A", nextS());
    EXPECT_EQ(')', lexer::get());
    EXPECT_EQ($, lexer::get());
  }
  {
    lexer::initialize(strdup("(a)"));
    Short token = lexer::get();
    EXPECT_EQ(token, '(');
    EXPECT_STREQ("A", nextS());
    EXPECT_EQ(')', lexer::get());
    EXPECT_EQ($, lexer::get());
  }
}

TEST(lexer, Empty) {
  t("");
  EXPECT_EQ($, next());
}

TEST(lexer, EmptyComment) {
  t(";foo bar");
  EXPECT_EQ($, next());
}

TEST(lexer, Char) {
  t("A");
  EXPECT_STREQ("A", nextS());
}

TEST(lexer, Atom) {
  t("atom");
  auto s = nextS();
  EXPECT_STREQ("ATOM", s);
}

TEST(lexer, AtomSpaced) {
  t(" atom  ");
  EXPECT_STREQ("ATOM", nextS());
}

TEST(lexer, AtomCommented) {
  t(" atom ; some comment ");
  EXPECT_STREQ("ATOM", nextS());
}

TEST(lexer, HelloWorld) {
  t("Hello World\n");
  EXPECT_STREQ("HELLO", nextS());
  EXPECT_STREQ("WORLD", nextS());
}

TEST(lexer, IdemPotent) {
  t("");
  EXPECT_EQ($, next());
  EXPECT_EQ($, next());
  EXPECT_EQ($, next());
}

TEST(lexer, OneComment) {
  t("Hello ;foo bar\n World");
  EXPECT_STREQ("HELLO", nextS());
  EXPECT_STREQ("WORLD", nextS());
  EXPECT_EQ($, next());
}

TEST(lexer, RemoveComments) {
  t("Hello ; foo bar \n World\n; foo bar");
  EXPECT_STREQ("HELLO", nextS());
  EXPECT_STREQ("WORLD", nextS());
}

TEST(lexer, HelloWorldEOF) {
  t("Hello World\n");
  EXPECT_STREQ("HELLO", nextS());
  EXPECT_STREQ("WORLD", nextS());
  EXPECT_EQ($, next());
}

TEST(lexer, HelloWorldEOFAgain) {
  t("Hello\n   World\n");
  EXPECT_STREQ("HELLO", nextS());
  EXPECT_STREQ("WORLD", nextS());
  EXPECT_EQ($, next());
}

TEST(lexer, ConcreteTokens) {
  using lexer::tokens;
  t(tokens);
  for (int i = 0; tokens[i] != '\0'; ++i)
    ASSERT_EQ(tokens[i], next());
}
