
// Generated from Sparql11.g4 by ANTLR 4.6

#pragma once


#include "antlr4-runtime.h"




class  Sparql11Lexer : public antlr4::Lexer {
public:
  enum {
    DATA = 1, MODIFY = 2, DELETE = 3, INSERT = 4, INTO = 5, LOAD = 6, CLEAR = 7, 
    CREATE = 8, SILENT = 9, DROP = 10, DEFAULT = 11, ALL = 12, SERVICE = 13, 
    MINUS_P = 14, EXISTS = 15, UNSAID = 16, HAVING = 17, COUNT = 18, SUM = 19, 
    MIN = 20, MAX = 21, AVG = 22, SAMPLE = 23, GROUP_CONCAT = 24, SEPARATOR = 25, 
    USING = 26, COALESCE = 27, DEFINE = 28, IF = 29, BASE = 30, PREFIX = 31, 
    IN = 32, NOT = 33, SELECT = 34, DISTINCT = 35, REDUCED = 36, CONSTRUCT = 37, 
    DESCRIBE = 38, ASK = 39, FROM = 40, NAMED = 41, WHERE = 42, ORDER = 43, 
    GROUP = 44, BY = 45, ASC = 46, DESC = 47, LIMIT = 48, OFFSET = 49, BINDINGS = 50, 
    WITH = 51, OPTIONAL = 52, GRAPH = 53, UNION = 54, FILTER = 55, A = 56, 
    AS = 57, STR = 58, LANG = 59, LANGMATCHES = 60, DATATYPE = 61, BOUND = 62, 
    SAMETERM = 63, IRI = 64, URI = 65, BNODE = 66, STRLANG = 67, STRDT = 68, 
    ISIRI = 69, ISURI = 70, ISBLANK = 71, ISLITERAL = 72, ISNUMERIC = 73, 
    REGEX = 74, TRUE = 75, FALSE = 76, IRI_REF = 77, PNAME_NS = 78, PNAME_LN = 79, 
    VAR1 = 80, VAR2 = 81, LANGTAG = 82, INTEGER = 83, DECIMAL = 84, DOUBLE = 85, 
    INTEGER_POSITIVE = 86, DECIMAL_POSITIVE = 87, DOUBLE_POSITIVE = 88, 
    INTEGER_NEGATIVE = 89, DECIMAL_NEGATIVE = 90, DOUBLE_NEGATIVE = 91, 
    STRING_LITERAL1 = 92, STRING_LITERAL2 = 93, STRING_LITERAL_LONG1 = 94, 
    STRING_LITERAL_LONG2 = 95, WS = 96, BLANK_NODE_LABEL = 97, REFERENCE = 98, 
    AND = 99, PIPE = 100, OR = 101, COMMENT = 102, OPEN_CURLY_BRACE = 103, 
    CLOSE_CURLY_BRACE = 104, SEMICOLON = 105, DOT = 106, PLUS = 107, MINUS = 108, 
    ASTERISK = 109, COMMA = 110, NOT_SIGN = 111, DIVIDE = 112, EQUAL = 113, 
    LESS = 114, GREATER = 115, OPEN_BRACE = 116, CLOSE_BRACE = 117, LESS_EQUAL = 118, 
    GREATER_EQUAL = 119, NOT_EQUAL = 120, OPEN_SQUARE_BRACE = 121, CLOSE_SQUARE_BRACE = 122, 
    HAT_LABEL = 123, QUESTION_MARK_LABEL = 124, UNDEF = 125
  };

  Sparql11Lexer(antlr4::CharStream *input);
  ~Sparql11Lexer();

  virtual std::string getGrammarFileName() const override;
  virtual const std::vector<std::string>& getRuleNames() const override;

  virtual const std::vector<std::string>& getModeNames() const override;
  virtual const std::vector<std::string>& getTokenNames() const override; // deprecated, use vocabulary instead
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

  virtual const std::vector<uint16_t> getSerializedATN() const override;
  virtual const antlr4::atn::ATN& getATN() const override;

private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;
  static std::vector<std::string> _modeNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

