
// Generated from Sparql11.g4 by ANTLR 4.6

#pragma once


#include "antlr4-runtime.h"




class  Sparql11Parser : public antlr4::Parser {
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

  enum {
    RuleQueryUnit = 0, RuleQuery = 1, RulePrologue = 2, RuleBaseDecl = 3, 
    RulePrefixDecl = 4, RuleSelectQuery = 5, RuleSubSelect = 6, RuleSelectClause = 7, 
    RuleConstructQuery = 8, RuleDescribeQuery = 9, RuleAskQuery = 10, RuleDatasetClause = 11, 
    RuleDefaultGraphClause = 12, RuleNamedGraphClause = 13, RuleSourceSelector = 14, 
    RuleWhereClause = 15, RuleSolutionModifier = 16, RuleGroupClause = 17, 
    RuleGroupCondition = 18, RuleHavingClause = 19, RuleHavingCondition = 20, 
    RuleOrderClause = 21, RuleOrderCondition = 22, RuleLimitOffsetClauses = 23, 
    RuleLimitClause = 24, RuleOffsetClause = 25, RuleBindingsClause = 26, 
    RuleBindingValue = 27, RuleUpdateUnit = 28, RuleUpdate = 29, RuleUpdate1 = 30, 
    RuleLoad = 31, RuleClear = 32, RuleDrop = 33, RuleCreate = 34, RuleInsertData = 35, 
    RuleDeleteData = 36, RuleDeleteWhere = 37, RuleModify = 38, RuleDeleteClause = 39, 
    RuleInsertClause = 40, RuleUsingClause = 41, RuleGraphRef = 42, RuleGraphRefAll = 43, 
    RuleQuadPattern = 44, RuleQuadData = 45, RuleQuads = 46, RuleQuadsNotTriples = 47, 
    RuleTriplesTemplate = 48, RuleGroupGraphPattern = 49, RuleGroupGraphPatternSub = 50, 
    RuleTriplesBlock = 51, RuleGraphPatternNotTriples = 52, RuleOptionalGraphPattern = 53, 
    RuleGraphGraphPattern = 54, RuleServiceGraphPattern = 55, RuleMinusGraphPattern = 56, 
    RuleGroupOrUnionGraphPattern = 57, RuleFilter = 58, RuleConstraint = 59, 
    RuleFunctionCall = 60, RuleArgList = 61, RuleExpressionList = 62, RuleConstructTemplate = 63, 
    RuleConstructTriples = 64, RuleTriplesSameSubject = 65, RulePropertyListNotEmpty = 66, 
    RulePropertyList = 67, RuleObjectList = 68, RuleObject = 69, RuleVerb = 70, 
    RuleTriplesSameSubjectPath = 71, RulePropertyListNotEmptyPath = 72, 
    RulePropertyListPath = 73, RuleVerbPath = 74, RuleVerbSimple = 75, RulePath = 76, 
    RulePathAlternative = 77, RulePathSequence = 78, RulePathElt = 79, RulePathEltOrInverse = 80, 
    RulePathMod = 81, RulePathPrimary = 82, RulePathNegatedPropertySet = 83, 
    RulePathOneInPropertySet = 84, RuleInteger = 85, RuleTriplesNode = 86, 
    RuleBlankNodePropertyList = 87, RuleCollection = 88, RuleGraphNode = 89, 
    RuleVarOrTerm = 90, RuleVarOrIriRef = 91, RuleVariable = 92, RuleGraphTerm = 93, 
    RuleExpression = 94, RuleConditionalOrExpression = 95, RuleConditionalAndExpression = 96, 
    RuleValueLogical = 97, RuleRelationalExpression = 98, RuleNumericExpression = 99, 
    RuleAdditiveExpression = 100, RuleMultiplicativeExpression = 101, RuleUnaryExpression = 102, 
    RulePrimaryExpression = 103, RuleBrackettedExpression = 104, RuleBuiltInCall = 105, 
    RuleRegexExpression = 106, RuleExistsFunc = 107, RuleNotExistsFunc = 108, 
    RuleAggregate = 109, RuleIriRefOrFunction = 110, RuleRdfLiteral = 111, 
    RuleNumericLiteral = 112, RuleNumericLiteralUnsigned = 113, RuleNumericLiteralPositive = 114, 
    RuleNumericLiteralNegative = 115, RuleBooleanLiteral = 116, RuleString = 117, 
    RuleIriRef = 118, RulePrefixedName = 119, RuleBlankNode = 120
  };

  Sparql11Parser(antlr4::TokenStream *input);
  ~Sparql11Parser();

  virtual std::string getGrammarFileName() const override;
  virtual const antlr4::atn::ATN& getATN() const override { return _atn; };
  virtual const std::vector<std::string>& getTokenNames() const override { return _tokenNames; }; // deprecated: use vocabulary instead.
  virtual const std::vector<std::string>& getRuleNames() const override;
  virtual antlr4::dfa::Vocabulary& getVocabulary() const override;


  class QueryUnitContext;
  class QueryContext;
  class PrologueContext;
  class BaseDeclContext;
  class PrefixDeclContext;
  class SelectQueryContext;
  class SubSelectContext;
  class SelectClauseContext;
  class ConstructQueryContext;
  class DescribeQueryContext;
  class AskQueryContext;
  class DatasetClauseContext;
  class DefaultGraphClauseContext;
  class NamedGraphClauseContext;
  class SourceSelectorContext;
  class WhereClauseContext;
  class SolutionModifierContext;
  class GroupClauseContext;
  class GroupConditionContext;
  class HavingClauseContext;
  class HavingConditionContext;
  class OrderClauseContext;
  class OrderConditionContext;
  class LimitOffsetClausesContext;
  class LimitClauseContext;
  class OffsetClauseContext;
  class BindingsClauseContext;
  class BindingValueContext;
  class UpdateUnitContext;
  class UpdateContext;
  class Update1Context;
  class LoadContext;
  class ClearContext;
  class DropContext;
  class CreateContext;
  class InsertDataContext;
  class DeleteDataContext;
  class DeleteWhereContext;
  class ModifyContext;
  class DeleteClauseContext;
  class InsertClauseContext;
  class UsingClauseContext;
  class GraphRefContext;
  class GraphRefAllContext;
  class QuadPatternContext;
  class QuadDataContext;
  class QuadsContext;
  class QuadsNotTriplesContext;
  class TriplesTemplateContext;
  class GroupGraphPatternContext;
  class GroupGraphPatternSubContext;
  class TriplesBlockContext;
  class GraphPatternNotTriplesContext;
  class OptionalGraphPatternContext;
  class GraphGraphPatternContext;
  class ServiceGraphPatternContext;
  class MinusGraphPatternContext;
  class GroupOrUnionGraphPatternContext;
  class FilterContext;
  class ConstraintContext;
  class FunctionCallContext;
  class ArgListContext;
  class ExpressionListContext;
  class ConstructTemplateContext;
  class ConstructTriplesContext;
  class TriplesSameSubjectContext;
  class PropertyListNotEmptyContext;
  class PropertyListContext;
  class ObjectListContext;
  class ObjectContext;
  class VerbContext;
  class TriplesSameSubjectPathContext;
  class PropertyListNotEmptyPathContext;
  class PropertyListPathContext;
  class VerbPathContext;
  class VerbSimpleContext;
  class PathContext;
  class PathAlternativeContext;
  class PathSequenceContext;
  class PathEltContext;
  class PathEltOrInverseContext;
  class PathModContext;
  class PathPrimaryContext;
  class PathNegatedPropertySetContext;
  class PathOneInPropertySetContext;
  class IntegerContext;
  class TriplesNodeContext;
  class BlankNodePropertyListContext;
  class CollectionContext;
  class GraphNodeContext;
  class VarOrTermContext;
  class VarOrIriRefContext;
  class VariableContext;
  class GraphTermContext;
  class ExpressionContext;
  class ConditionalOrExpressionContext;
  class ConditionalAndExpressionContext;
  class ValueLogicalContext;
  class RelationalExpressionContext;
  class NumericExpressionContext;
  class AdditiveExpressionContext;
  class MultiplicativeExpressionContext;
  class UnaryExpressionContext;
  class PrimaryExpressionContext;
  class BrackettedExpressionContext;
  class BuiltInCallContext;
  class RegexExpressionContext;
  class ExistsFuncContext;
  class NotExistsFuncContext;
  class AggregateContext;
  class IriRefOrFunctionContext;
  class RdfLiteralContext;
  class NumericLiteralContext;
  class NumericLiteralUnsignedContext;
  class NumericLiteralPositiveContext;
  class NumericLiteralNegativeContext;
  class BooleanLiteralContext;
  class StringContext;
  class IriRefContext;
  class PrefixedNameContext;
  class BlankNodeContext; 

  class  QueryUnitContext : public antlr4::ParserRuleContext {
  public:
    QueryUnitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    QueryContext *query();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  QueryUnitContext* queryUnit();

  class  QueryContext : public antlr4::ParserRuleContext {
  public:
    QueryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PrologueContext *prologue();
    SelectQueryContext *selectQuery();
    ConstructQueryContext *constructQuery();
    DescribeQueryContext *describeQuery();
    AskQueryContext *askQuery();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  QueryContext* query();

  class  PrologueContext : public antlr4::ParserRuleContext {
  public:
    PrologueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BaseDeclContext *baseDecl();
    std::vector<PrefixDeclContext *> prefixDecl();
    PrefixDeclContext* prefixDecl(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PrologueContext* prologue();

  class  BaseDeclContext : public antlr4::ParserRuleContext {
  public:
    BaseDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BASE();
    antlr4::tree::TerminalNode *IRI_REF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BaseDeclContext* baseDecl();

  class  PrefixDeclContext : public antlr4::ParserRuleContext {
  public:
    PrefixDeclContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PREFIX();
    antlr4::tree::TerminalNode *PNAME_NS();
    antlr4::tree::TerminalNode *IRI_REF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PrefixDeclContext* prefixDecl();

  class  SelectQueryContext : public antlr4::ParserRuleContext {
  public:
    SelectQueryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SelectClauseContext *selectClause();
    WhereClauseContext *whereClause();
    SolutionModifierContext *solutionModifier();
    BindingsClauseContext *bindingsClause();
    std::vector<DatasetClauseContext *> datasetClause();
    DatasetClauseContext* datasetClause(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SelectQueryContext* selectQuery();

  class  SubSelectContext : public antlr4::ParserRuleContext {
  public:
    SubSelectContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SelectClauseContext *selectClause();
    WhereClauseContext *whereClause();
    SolutionModifierContext *solutionModifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SubSelectContext* subSelect();

  class  SelectClauseContext : public antlr4::ParserRuleContext {
  public:
    SelectClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SELECT();
    antlr4::tree::TerminalNode *ASTERISK();
    antlr4::tree::TerminalNode *DISTINCT();
    antlr4::tree::TerminalNode *REDUCED();
    std::vector<VariableContext *> variable();
    VariableContext* variable(size_t i);
    std::vector<antlr4::tree::TerminalNode *> OPEN_BRACE();
    antlr4::tree::TerminalNode* OPEN_BRACE(size_t i);
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> AS();
    antlr4::tree::TerminalNode* AS(size_t i);
    std::vector<antlr4::tree::TerminalNode *> CLOSE_BRACE();
    antlr4::tree::TerminalNode* CLOSE_BRACE(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SelectClauseContext* selectClause();

  class  ConstructQueryContext : public antlr4::ParserRuleContext {
  public:
    ConstructQueryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CONSTRUCT();
    ConstructTemplateContext *constructTemplate();
    WhereClauseContext *whereClause();
    SolutionModifierContext *solutionModifier();
    std::vector<DatasetClauseContext *> datasetClause();
    DatasetClauseContext* datasetClause(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConstructQueryContext* constructQuery();

  class  DescribeQueryContext : public antlr4::ParserRuleContext {
  public:
    DescribeQueryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DESCRIBE();
    SolutionModifierContext *solutionModifier();
    antlr4::tree::TerminalNode *ASTERISK();
    std::vector<DatasetClauseContext *> datasetClause();
    DatasetClauseContext* datasetClause(size_t i);
    WhereClauseContext *whereClause();
    std::vector<VarOrIriRefContext *> varOrIriRef();
    VarOrIriRefContext* varOrIriRef(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DescribeQueryContext* describeQuery();

  class  AskQueryContext : public antlr4::ParserRuleContext {
  public:
    AskQueryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ASK();
    WhereClauseContext *whereClause();
    std::vector<DatasetClauseContext *> datasetClause();
    DatasetClauseContext* datasetClause(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AskQueryContext* askQuery();

  class  DatasetClauseContext : public antlr4::ParserRuleContext {
  public:
    DatasetClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FROM();
    DefaultGraphClauseContext *defaultGraphClause();
    NamedGraphClauseContext *namedGraphClause();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DatasetClauseContext* datasetClause();

  class  DefaultGraphClauseContext : public antlr4::ParserRuleContext {
  public:
    DefaultGraphClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SourceSelectorContext *sourceSelector();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DefaultGraphClauseContext* defaultGraphClause();

  class  NamedGraphClauseContext : public antlr4::ParserRuleContext {
  public:
    NamedGraphClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NAMED();
    SourceSelectorContext *sourceSelector();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NamedGraphClauseContext* namedGraphClause();

  class  SourceSelectorContext : public antlr4::ParserRuleContext {
  public:
    SourceSelectorContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IriRefContext *iriRef();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SourceSelectorContext* sourceSelector();

  class  WhereClauseContext : public antlr4::ParserRuleContext {
  public:
    WhereClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    GroupGraphPatternContext *groupGraphPattern();
    antlr4::tree::TerminalNode *WHERE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  WhereClauseContext* whereClause();

  class  SolutionModifierContext : public antlr4::ParserRuleContext {
  public:
    SolutionModifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    GroupClauseContext *groupClause();
    HavingClauseContext *havingClause();
    OrderClauseContext *orderClause();
    LimitOffsetClausesContext *limitOffsetClauses();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  SolutionModifierContext* solutionModifier();

  class  GroupClauseContext : public antlr4::ParserRuleContext {
  public:
    GroupClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *GROUP();
    antlr4::tree::TerminalNode *BY();
    std::vector<GroupConditionContext *> groupCondition();
    GroupConditionContext* groupCondition(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  GroupClauseContext* groupClause();

  class  GroupConditionContext : public antlr4::ParserRuleContext {
  public:
    GroupConditionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BuiltInCallContext *builtInCall();
    FunctionCallContext *functionCall();
    antlr4::tree::TerminalNode *OPEN_BRACE();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *CLOSE_BRACE();
    antlr4::tree::TerminalNode *AS();
    VariableContext *variable();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  GroupConditionContext* groupCondition();

  class  HavingClauseContext : public antlr4::ParserRuleContext {
  public:
    HavingClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *HAVING();
    std::vector<HavingConditionContext *> havingCondition();
    HavingConditionContext* havingCondition(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  HavingClauseContext* havingClause();

  class  HavingConditionContext : public antlr4::ParserRuleContext {
  public:
    HavingConditionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConstraintContext *constraint();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  HavingConditionContext* havingCondition();

  class  OrderClauseContext : public antlr4::ParserRuleContext {
  public:
    OrderClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ORDER();
    antlr4::tree::TerminalNode *BY();
    std::vector<OrderConditionContext *> orderCondition();
    OrderConditionContext* orderCondition(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  OrderClauseContext* orderClause();

  class  OrderConditionContext : public antlr4::ParserRuleContext {
  public:
    OrderConditionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BrackettedExpressionContext *brackettedExpression();
    antlr4::tree::TerminalNode *ASC();
    antlr4::tree::TerminalNode *DESC();
    ConstraintContext *constraint();
    VariableContext *variable();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  OrderConditionContext* orderCondition();

  class  LimitOffsetClausesContext : public antlr4::ParserRuleContext {
  public:
    LimitOffsetClausesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LimitClauseContext *limitClause();
    OffsetClauseContext *offsetClause();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LimitOffsetClausesContext* limitOffsetClauses();

  class  LimitClauseContext : public antlr4::ParserRuleContext {
  public:
    LimitClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LIMIT();
    antlr4::tree::TerminalNode *INTEGER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LimitClauseContext* limitClause();

  class  OffsetClauseContext : public antlr4::ParserRuleContext {
  public:
    OffsetClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OFFSET();
    antlr4::tree::TerminalNode *INTEGER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  OffsetClauseContext* offsetClause();

  class  BindingsClauseContext : public antlr4::ParserRuleContext {
  public:
    BindingsClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BINDINGS();
    antlr4::tree::TerminalNode *OPEN_CURLY_BRACE();
    antlr4::tree::TerminalNode *CLOSE_CURLY_BRACE();
    std::vector<VariableContext *> variable();
    VariableContext* variable(size_t i);
    std::vector<antlr4::tree::TerminalNode *> OPEN_BRACE();
    antlr4::tree::TerminalNode* OPEN_BRACE(size_t i);
    std::vector<antlr4::tree::TerminalNode *> CLOSE_BRACE();
    antlr4::tree::TerminalNode* CLOSE_BRACE(size_t i);
    std::vector<BindingValueContext *> bindingValue();
    BindingValueContext* bindingValue(size_t i);
    std::vector<antlr4::tree::TerminalNode *> WS();
    antlr4::tree::TerminalNode* WS(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BindingsClauseContext* bindingsClause();

  class  BindingValueContext : public antlr4::ParserRuleContext {
  public:
    BindingValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IriRefContext *iriRef();
    RdfLiteralContext *rdfLiteral();
    NumericLiteralContext *numericLiteral();
    BooleanLiteralContext *booleanLiteral();
    antlr4::tree::TerminalNode *UNDEF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BindingValueContext* bindingValue();

  class  UpdateUnitContext : public antlr4::ParserRuleContext {
  public:
    UpdateUnitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    UpdateContext *update();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  UpdateUnitContext* updateUnit();

  class  UpdateContext : public antlr4::ParserRuleContext {
  public:
    UpdateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PrologueContext *prologue();
    Update1Context *update1();
    antlr4::tree::TerminalNode *SEMICOLON();
    UpdateContext *update();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  UpdateContext* update();

  class  Update1Context : public antlr4::ParserRuleContext {
  public:
    Update1Context(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LoadContext *load();
    ClearContext *clear();
    DropContext *drop();
    CreateContext *create();
    InsertDataContext *insertData();
    DeleteDataContext *deleteData();
    DeleteWhereContext *deleteWhere();
    ModifyContext *modify();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  Update1Context* update1();

  class  LoadContext : public antlr4::ParserRuleContext {
  public:
    LoadContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LOAD();
    IriRefContext *iriRef();
    antlr4::tree::TerminalNode *INTO();
    GraphRefContext *graphRef();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  LoadContext* load();

  class  ClearContext : public antlr4::ParserRuleContext {
  public:
    ClearContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CLEAR();
    GraphRefAllContext *graphRefAll();
    antlr4::tree::TerminalNode *SILENT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ClearContext* clear();

  class  DropContext : public antlr4::ParserRuleContext {
  public:
    DropContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DROP();
    GraphRefAllContext *graphRefAll();
    antlr4::tree::TerminalNode *SILENT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DropContext* drop();

  class  CreateContext : public antlr4::ParserRuleContext {
  public:
    CreateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CREATE();
    GraphRefContext *graphRef();
    antlr4::tree::TerminalNode *SILENT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CreateContext* create();

  class  InsertDataContext : public antlr4::ParserRuleContext {
  public:
    InsertDataContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INSERT();
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *DATA();
    QuadDataContext *quadData();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  InsertDataContext* insertData();

  class  DeleteDataContext : public antlr4::ParserRuleContext {
  public:
    DeleteDataContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DELETE();
    antlr4::tree::TerminalNode *DATA();
    QuadDataContext *quadData();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DeleteDataContext* deleteData();

  class  DeleteWhereContext : public antlr4::ParserRuleContext {
  public:
    DeleteWhereContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DELETE();
    antlr4::tree::TerminalNode *WHERE();
    QuadPatternContext *quadPattern();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DeleteWhereContext* deleteWhere();

  class  ModifyContext : public antlr4::ParserRuleContext {
  public:
    ModifyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WHERE();
    GroupGraphPatternContext *groupGraphPattern();
    DeleteClauseContext *deleteClause();
    InsertClauseContext *insertClause();
    antlr4::tree::TerminalNode *WITH();
    IriRefContext *iriRef();
    std::vector<UsingClauseContext *> usingClause();
    UsingClauseContext* usingClause(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ModifyContext* modify();

  class  DeleteClauseContext : public antlr4::ParserRuleContext {
  public:
    DeleteClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DELETE();
    QuadPatternContext *quadPattern();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  DeleteClauseContext* deleteClause();

  class  InsertClauseContext : public antlr4::ParserRuleContext {
  public:
    InsertClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INSERT();
    QuadPatternContext *quadPattern();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  InsertClauseContext* insertClause();

  class  UsingClauseContext : public antlr4::ParserRuleContext {
  public:
    UsingClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *USING();
    IriRefContext *iriRef();
    antlr4::tree::TerminalNode *NAMED();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  UsingClauseContext* usingClause();

  class  GraphRefContext : public antlr4::ParserRuleContext {
  public:
    GraphRefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *GRAPH();
    IriRefContext *iriRef();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  GraphRefContext* graphRef();

  class  GraphRefAllContext : public antlr4::ParserRuleContext {
  public:
    GraphRefAllContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    GraphRefContext *graphRef();
    antlr4::tree::TerminalNode *DEFAULT();
    antlr4::tree::TerminalNode *NAMED();
    antlr4::tree::TerminalNode *ALL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  GraphRefAllContext* graphRefAll();

  class  QuadPatternContext : public antlr4::ParserRuleContext {
  public:
    QuadPatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OPEN_CURLY_BRACE();
    QuadsContext *quads();
    antlr4::tree::TerminalNode *CLOSE_CURLY_BRACE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  QuadPatternContext* quadPattern();

  class  QuadDataContext : public antlr4::ParserRuleContext {
  public:
    QuadDataContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OPEN_CURLY_BRACE();
    QuadsContext *quads();
    antlr4::tree::TerminalNode *CLOSE_CURLY_BRACE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  QuadDataContext* quadData();

  class  QuadsContext : public antlr4::ParserRuleContext {
  public:
    QuadsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TriplesTemplateContext *> triplesTemplate();
    TriplesTemplateContext* triplesTemplate(size_t i);
    std::vector<QuadsNotTriplesContext *> quadsNotTriples();
    QuadsNotTriplesContext* quadsNotTriples(size_t i);
    std::vector<antlr4::tree::TerminalNode *> DOT();
    antlr4::tree::TerminalNode* DOT(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  QuadsContext* quads();

  class  QuadsNotTriplesContext : public antlr4::ParserRuleContext {
  public:
    QuadsNotTriplesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *GRAPH();
    VarOrIriRefContext *varOrIriRef();
    antlr4::tree::TerminalNode *OPEN_CURLY_BRACE();
    TriplesTemplateContext *triplesTemplate();
    antlr4::tree::TerminalNode *CLOSE_CURLY_BRACE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  QuadsNotTriplesContext* quadsNotTriples();

  class  TriplesTemplateContext : public antlr4::ParserRuleContext {
  public:
    TriplesTemplateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TriplesSameSubjectContext *triplesSameSubject();
    antlr4::tree::TerminalNode *DOT();
    TriplesTemplateContext *triplesTemplate();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TriplesTemplateContext* triplesTemplate();

  class  GroupGraphPatternContext : public antlr4::ParserRuleContext {
  public:
    GroupGraphPatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OPEN_CURLY_BRACE();
    antlr4::tree::TerminalNode *CLOSE_CURLY_BRACE();
    SubSelectContext *subSelect();
    GroupGraphPatternSubContext *groupGraphPatternSub();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  GroupGraphPatternContext* groupGraphPattern();

  class  GroupGraphPatternSubContext : public antlr4::ParserRuleContext {
  public:
    GroupGraphPatternSubContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TriplesBlockContext *> triplesBlock();
    TriplesBlockContext* triplesBlock(size_t i);
    std::vector<GraphPatternNotTriplesContext *> graphPatternNotTriples();
    GraphPatternNotTriplesContext* graphPatternNotTriples(size_t i);
    std::vector<antlr4::tree::TerminalNode *> DOT();
    antlr4::tree::TerminalNode* DOT(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  GroupGraphPatternSubContext* groupGraphPatternSub();

  class  TriplesBlockContext : public antlr4::ParserRuleContext {
  public:
    TriplesBlockContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TriplesSameSubjectPathContext *triplesSameSubjectPath();
    antlr4::tree::TerminalNode *DOT();
    TriplesBlockContext *triplesBlock();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TriplesBlockContext* triplesBlock();

  class  GraphPatternNotTriplesContext : public antlr4::ParserRuleContext {
  public:
    GraphPatternNotTriplesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    GroupOrUnionGraphPatternContext *groupOrUnionGraphPattern();
    OptionalGraphPatternContext *optionalGraphPattern();
    MinusGraphPatternContext *minusGraphPattern();
    GraphGraphPatternContext *graphGraphPattern();
    ServiceGraphPatternContext *serviceGraphPattern();
    FilterContext *filter();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  GraphPatternNotTriplesContext* graphPatternNotTriples();

  class  OptionalGraphPatternContext : public antlr4::ParserRuleContext {
  public:
    OptionalGraphPatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OPTIONAL();
    GroupGraphPatternContext *groupGraphPattern();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  OptionalGraphPatternContext* optionalGraphPattern();

  class  GraphGraphPatternContext : public antlr4::ParserRuleContext {
  public:
    GraphGraphPatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *GRAPH();
    VarOrIriRefContext *varOrIriRef();
    GroupGraphPatternContext *groupGraphPattern();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  GraphGraphPatternContext* graphGraphPattern();

  class  ServiceGraphPatternContext : public antlr4::ParserRuleContext {
  public:
    ServiceGraphPatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SERVICE();
    VarOrIriRefContext *varOrIriRef();
    GroupGraphPatternContext *groupGraphPattern();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ServiceGraphPatternContext* serviceGraphPattern();

  class  MinusGraphPatternContext : public antlr4::ParserRuleContext {
  public:
    MinusGraphPatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *MINUS_P();
    GroupGraphPatternContext *groupGraphPattern();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MinusGraphPatternContext* minusGraphPattern();

  class  GroupOrUnionGraphPatternContext : public antlr4::ParserRuleContext {
  public:
    GroupOrUnionGraphPatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<GroupGraphPatternContext *> groupGraphPattern();
    GroupGraphPatternContext* groupGraphPattern(size_t i);
    std::vector<antlr4::tree::TerminalNode *> UNION();
    antlr4::tree::TerminalNode* UNION(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  GroupOrUnionGraphPatternContext* groupOrUnionGraphPattern();

  class  FilterContext : public antlr4::ParserRuleContext {
  public:
    FilterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FILTER();
    ConstraintContext *constraint();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FilterContext* filter();

  class  ConstraintContext : public antlr4::ParserRuleContext {
  public:
    ConstraintContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BrackettedExpressionContext *brackettedExpression();
    BuiltInCallContext *builtInCall();
    FunctionCallContext *functionCall();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConstraintContext* constraint();

  class  FunctionCallContext : public antlr4::ParserRuleContext {
  public:
    FunctionCallContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IriRefContext *iriRef();
    ArgListContext *argList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  FunctionCallContext* functionCall();

  class  ArgListContext : public antlr4::ParserRuleContext {
  public:
    ArgListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OPEN_BRACE();
    antlr4::tree::TerminalNode *CLOSE_BRACE();
    std::vector<antlr4::tree::TerminalNode *> WS();
    antlr4::tree::TerminalNode* WS(size_t i);
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *DISTINCT();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ArgListContext* argList();

  class  ExpressionListContext : public antlr4::ParserRuleContext {
  public:
    ExpressionListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OPEN_BRACE();
    antlr4::tree::TerminalNode *CLOSE_BRACE();
    std::vector<antlr4::tree::TerminalNode *> WS();
    antlr4::tree::TerminalNode* WS(size_t i);
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExpressionListContext* expressionList();

  class  ConstructTemplateContext : public antlr4::ParserRuleContext {
  public:
    ConstructTemplateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OPEN_CURLY_BRACE();
    antlr4::tree::TerminalNode *CLOSE_CURLY_BRACE();
    ConstructTriplesContext *constructTriples();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConstructTemplateContext* constructTemplate();

  class  ConstructTriplesContext : public antlr4::ParserRuleContext {
  public:
    ConstructTriplesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    TriplesSameSubjectContext *triplesSameSubject();
    antlr4::tree::TerminalNode *DOT();
    ConstructTriplesContext *constructTriples();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConstructTriplesContext* constructTriples();

  class  TriplesSameSubjectContext : public antlr4::ParserRuleContext {
  public:
    TriplesSameSubjectContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VarOrTermContext *varOrTerm();
    PropertyListNotEmptyContext *propertyListNotEmpty();
    TriplesNodeContext *triplesNode();
    PropertyListContext *propertyList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TriplesSameSubjectContext* triplesSameSubject();

  class  PropertyListNotEmptyContext : public antlr4::ParserRuleContext {
  public:
    PropertyListNotEmptyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<VerbContext *> verb();
    VerbContext* verb(size_t i);
    std::vector<ObjectListContext *> objectList();
    ObjectListContext* objectList(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SEMICOLON();
    antlr4::tree::TerminalNode* SEMICOLON(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PropertyListNotEmptyContext* propertyListNotEmpty();

  class  PropertyListContext : public antlr4::ParserRuleContext {
  public:
    PropertyListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PropertyListNotEmptyContext *propertyListNotEmpty();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PropertyListContext* propertyList();

  class  ObjectListContext : public antlr4::ParserRuleContext {
  public:
    ObjectListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ObjectContext *> object();
    ObjectContext* object(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ObjectListContext* objectList();

  class  ObjectContext : public antlr4::ParserRuleContext {
  public:
    ObjectContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    GraphNodeContext *graphNode();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ObjectContext* object();

  class  VerbContext : public antlr4::ParserRuleContext {
  public:
    VerbContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VarOrIriRefContext *varOrIriRef();
    antlr4::tree::TerminalNode *A();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VerbContext* verb();

  class  TriplesSameSubjectPathContext : public antlr4::ParserRuleContext {
  public:
    TriplesSameSubjectPathContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VarOrTermContext *varOrTerm();
    PropertyListNotEmptyPathContext *propertyListNotEmptyPath();
    TriplesNodeContext *triplesNode();
    PropertyListPathContext *propertyListPath();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TriplesSameSubjectPathContext* triplesSameSubjectPath();

  class  PropertyListNotEmptyPathContext : public antlr4::ParserRuleContext {
  public:
    PropertyListNotEmptyPathContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ObjectListContext *> objectList();
    ObjectListContext* objectList(size_t i);
    std::vector<VerbPathContext *> verbPath();
    VerbPathContext* verbPath(size_t i);
    std::vector<VerbSimpleContext *> verbSimple();
    VerbSimpleContext* verbSimple(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SEMICOLON();
    antlr4::tree::TerminalNode* SEMICOLON(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PropertyListNotEmptyPathContext* propertyListNotEmptyPath();

  class  PropertyListPathContext : public antlr4::ParserRuleContext {
  public:
    PropertyListPathContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PropertyListNotEmptyContext *propertyListNotEmpty();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PropertyListPathContext* propertyListPath();

  class  VerbPathContext : public antlr4::ParserRuleContext {
  public:
    VerbPathContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PathContext *path();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VerbPathContext* verbPath();

  class  VerbSimpleContext : public antlr4::ParserRuleContext {
  public:
    VerbSimpleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VariableContext *variable();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VerbSimpleContext* verbSimple();

  class  PathContext : public antlr4::ParserRuleContext {
  public:
    PathContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PathAlternativeContext *pathAlternative();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PathContext* path();

  class  PathAlternativeContext : public antlr4::ParserRuleContext {
  public:
    PathAlternativeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<PathSequenceContext *> pathSequence();
    PathSequenceContext* pathSequence(size_t i);
    std::vector<antlr4::tree::TerminalNode *> PIPE();
    antlr4::tree::TerminalNode* PIPE(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PathAlternativeContext* pathAlternative();

  class  PathSequenceContext : public antlr4::ParserRuleContext {
  public:
    PathSequenceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<PathEltOrInverseContext *> pathEltOrInverse();
    PathEltOrInverseContext* pathEltOrInverse(size_t i);
    std::vector<antlr4::tree::TerminalNode *> DIVIDE();
    antlr4::tree::TerminalNode* DIVIDE(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PathSequenceContext* pathSequence();

  class  PathEltContext : public antlr4::ParserRuleContext {
  public:
    PathEltContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PathPrimaryContext *pathPrimary();
    PathModContext *pathMod();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PathEltContext* pathElt();

  class  PathEltOrInverseContext : public antlr4::ParserRuleContext {
  public:
    PathEltOrInverseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PathEltContext *pathElt();
    antlr4::tree::TerminalNode *HAT_LABEL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PathEltOrInverseContext* pathEltOrInverse();

  class  PathModContext : public antlr4::ParserRuleContext {
  public:
    PathModContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ASTERISK();
    antlr4::tree::TerminalNode *QUESTION_MARK_LABEL();
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *OPEN_CURLY_BRACE();
    std::vector<IntegerContext *> integer();
    IntegerContext* integer(size_t i);
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *CLOSE_CURLY_BRACE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PathModContext* pathMod();

  class  PathPrimaryContext : public antlr4::ParserRuleContext {
  public:
    PathPrimaryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IriRefContext *iriRef();
    antlr4::tree::TerminalNode *A();
    antlr4::tree::TerminalNode *NOT_SIGN();
    PathNegatedPropertySetContext *pathNegatedPropertySet();
    antlr4::tree::TerminalNode *OPEN_BRACE();
    PathContext *path();
    antlr4::tree::TerminalNode *CLOSE_BRACE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PathPrimaryContext* pathPrimary();

  class  PathNegatedPropertySetContext : public antlr4::ParserRuleContext {
  public:
    PathNegatedPropertySetContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<PathOneInPropertySetContext *> pathOneInPropertySet();
    PathOneInPropertySetContext* pathOneInPropertySet(size_t i);
    antlr4::tree::TerminalNode *OPEN_BRACE();
    antlr4::tree::TerminalNode *CLOSE_BRACE();
    std::vector<antlr4::tree::TerminalNode *> PIPE();
    antlr4::tree::TerminalNode* PIPE(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PathNegatedPropertySetContext* pathNegatedPropertySet();

  class  PathOneInPropertySetContext : public antlr4::ParserRuleContext {
  public:
    PathOneInPropertySetContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IriRefContext *iriRef();
    antlr4::tree::TerminalNode *A();
    antlr4::tree::TerminalNode *HAT_LABEL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PathOneInPropertySetContext* pathOneInPropertySet();

  class  IntegerContext : public antlr4::ParserRuleContext {
  public:
    IntegerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INTEGER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IntegerContext* integer();

  class  TriplesNodeContext : public antlr4::ParserRuleContext {
  public:
    TriplesNodeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CollectionContext *collection();
    BlankNodePropertyListContext *blankNodePropertyList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  TriplesNodeContext* triplesNode();

  class  BlankNodePropertyListContext : public antlr4::ParserRuleContext {
  public:
    BlankNodePropertyListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OPEN_SQUARE_BRACE();
    PropertyListNotEmptyContext *propertyListNotEmpty();
    antlr4::tree::TerminalNode *CLOSE_SQUARE_BRACE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BlankNodePropertyListContext* blankNodePropertyList();

  class  CollectionContext : public antlr4::ParserRuleContext {
  public:
    CollectionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OPEN_BRACE();
    antlr4::tree::TerminalNode *CLOSE_BRACE();
    std::vector<GraphNodeContext *> graphNode();
    GraphNodeContext* graphNode(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  CollectionContext* collection();

  class  GraphNodeContext : public antlr4::ParserRuleContext {
  public:
    GraphNodeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VarOrTermContext *varOrTerm();
    TriplesNodeContext *triplesNode();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  GraphNodeContext* graphNode();

  class  VarOrTermContext : public antlr4::ParserRuleContext {
  public:
    VarOrTermContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VariableContext *variable();
    GraphTermContext *graphTerm();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VarOrTermContext* varOrTerm();

  class  VarOrIriRefContext : public antlr4::ParserRuleContext {
  public:
    VarOrIriRefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    VariableContext *variable();
    IriRefContext *iriRef();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VarOrIriRefContext* varOrIriRef();

  class  VariableContext : public antlr4::ParserRuleContext {
  public:
    VariableContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VAR1();
    antlr4::tree::TerminalNode *VAR2();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  VariableContext* variable();

  class  GraphTermContext : public antlr4::ParserRuleContext {
  public:
    GraphTermContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IriRefContext *iriRef();
    RdfLiteralContext *rdfLiteral();
    NumericLiteralContext *numericLiteral();
    BooleanLiteralContext *booleanLiteral();
    BlankNodeContext *blankNode();
    antlr4::tree::TerminalNode *OPEN_BRACE();
    antlr4::tree::TerminalNode *CLOSE_BRACE();
    std::vector<antlr4::tree::TerminalNode *> WS();
    antlr4::tree::TerminalNode* WS(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  GraphTermContext* graphTerm();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ConditionalOrExpressionContext *conditionalOrExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExpressionContext* expression();

  class  ConditionalOrExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionalOrExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ConditionalAndExpressionContext *> conditionalAndExpression();
    ConditionalAndExpressionContext* conditionalAndExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> OR();
    antlr4::tree::TerminalNode* OR(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConditionalOrExpressionContext* conditionalOrExpression();

  class  ConditionalAndExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionalAndExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ValueLogicalContext *> valueLogical();
    ValueLogicalContext* valueLogical(size_t i);
    std::vector<antlr4::tree::TerminalNode *> AND();
    antlr4::tree::TerminalNode* AND(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ConditionalAndExpressionContext* conditionalAndExpression();

  class  ValueLogicalContext : public antlr4::ParserRuleContext {
  public:
    ValueLogicalContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    RelationalExpressionContext *relationalExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ValueLogicalContext* valueLogical();

  class  RelationalExpressionContext : public antlr4::ParserRuleContext {
  public:
    RelationalExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<NumericExpressionContext *> numericExpression();
    NumericExpressionContext* numericExpression(size_t i);
    antlr4::tree::TerminalNode *EQUAL();
    antlr4::tree::TerminalNode *NOT_EQUAL();
    antlr4::tree::TerminalNode *LESS();
    antlr4::tree::TerminalNode *GREATER();
    antlr4::tree::TerminalNode *LESS_EQUAL();
    antlr4::tree::TerminalNode *GREATER_EQUAL();
    antlr4::tree::TerminalNode *IN();
    ExpressionListContext *expressionList();
    antlr4::tree::TerminalNode *NOT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  RelationalExpressionContext* relationalExpression();

  class  NumericExpressionContext : public antlr4::ParserRuleContext {
  public:
    NumericExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    AdditiveExpressionContext *additiveExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NumericExpressionContext* numericExpression();

  class  AdditiveExpressionContext : public antlr4::ParserRuleContext {
  public:
    AdditiveExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<MultiplicativeExpressionContext *> multiplicativeExpression();
    MultiplicativeExpressionContext* multiplicativeExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> PLUS();
    antlr4::tree::TerminalNode* PLUS(size_t i);
    std::vector<antlr4::tree::TerminalNode *> MINUS();
    antlr4::tree::TerminalNode* MINUS(size_t i);
    std::vector<NumericLiteralPositiveContext *> numericLiteralPositive();
    NumericLiteralPositiveContext* numericLiteralPositive(size_t i);
    std::vector<NumericLiteralNegativeContext *> numericLiteralNegative();
    NumericLiteralNegativeContext* numericLiteralNegative(size_t i);
    std::vector<antlr4::tree::TerminalNode *> ASTERISK();
    antlr4::tree::TerminalNode* ASTERISK(size_t i);
    std::vector<UnaryExpressionContext *> unaryExpression();
    UnaryExpressionContext* unaryExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> DIVIDE();
    antlr4::tree::TerminalNode* DIVIDE(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AdditiveExpressionContext* additiveExpression();

  class  MultiplicativeExpressionContext : public antlr4::ParserRuleContext {
  public:
    MultiplicativeExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<UnaryExpressionContext *> unaryExpression();
    UnaryExpressionContext* unaryExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> ASTERISK();
    antlr4::tree::TerminalNode* ASTERISK(size_t i);
    std::vector<antlr4::tree::TerminalNode *> DIVIDE();
    antlr4::tree::TerminalNode* DIVIDE(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  MultiplicativeExpressionContext* multiplicativeExpression();

  class  UnaryExpressionContext : public antlr4::ParserRuleContext {
  public:
    UnaryExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NOT_SIGN();
    PrimaryExpressionContext *primaryExpression();
    antlr4::tree::TerminalNode *PLUS();
    antlr4::tree::TerminalNode *MINUS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  UnaryExpressionContext* unaryExpression();

  class  PrimaryExpressionContext : public antlr4::ParserRuleContext {
  public:
    PrimaryExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BrackettedExpressionContext *brackettedExpression();
    BuiltInCallContext *builtInCall();
    IriRefOrFunctionContext *iriRefOrFunction();
    RdfLiteralContext *rdfLiteral();
    NumericLiteralContext *numericLiteral();
    BooleanLiteralContext *booleanLiteral();
    VariableContext *variable();
    AggregateContext *aggregate();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PrimaryExpressionContext* primaryExpression();

  class  BrackettedExpressionContext : public antlr4::ParserRuleContext {
  public:
    BrackettedExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OPEN_BRACE();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *CLOSE_BRACE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BrackettedExpressionContext* brackettedExpression();

  class  BuiltInCallContext : public antlr4::ParserRuleContext {
  public:
    BuiltInCallContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STR();
    antlr4::tree::TerminalNode *OPEN_BRACE();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *CLOSE_BRACE();
    antlr4::tree::TerminalNode *LANG();
    antlr4::tree::TerminalNode *LANGMATCHES();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    antlr4::tree::TerminalNode *DATATYPE();
    antlr4::tree::TerminalNode *BOUND();
    VariableContext *variable();
    antlr4::tree::TerminalNode *IRI();
    antlr4::tree::TerminalNode *URI();
    antlr4::tree::TerminalNode *BNODE();
    std::vector<antlr4::tree::TerminalNode *> WS();
    antlr4::tree::TerminalNode* WS(size_t i);
    antlr4::tree::TerminalNode *COALESCE();
    ExpressionListContext *expressionList();
    antlr4::tree::TerminalNode *IF();
    antlr4::tree::TerminalNode *STRLANG();
    antlr4::tree::TerminalNode *STRDT();
    antlr4::tree::TerminalNode *SAMETERM();
    antlr4::tree::TerminalNode *ISIRI();
    antlr4::tree::TerminalNode *ISURI();
    antlr4::tree::TerminalNode *ISBLANK();
    antlr4::tree::TerminalNode *ISLITERAL();
    antlr4::tree::TerminalNode *ISNUMERIC();
    RegexExpressionContext *regexExpression();
    ExistsFuncContext *existsFunc();
    NotExistsFuncContext *notExistsFunc();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BuiltInCallContext* builtInCall();

  class  RegexExpressionContext : public antlr4::ParserRuleContext {
  public:
    RegexExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *REGEX();
    antlr4::tree::TerminalNode *OPEN_BRACE();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    antlr4::tree::TerminalNode *CLOSE_BRACE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  RegexExpressionContext* regexExpression();

  class  ExistsFuncContext : public antlr4::ParserRuleContext {
  public:
    ExistsFuncContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EXISTS();
    GroupGraphPatternContext *groupGraphPattern();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  ExistsFuncContext* existsFunc();

  class  NotExistsFuncContext : public antlr4::ParserRuleContext {
  public:
    NotExistsFuncContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NOT();
    antlr4::tree::TerminalNode *EXISTS();
    GroupGraphPatternContext *groupGraphPattern();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NotExistsFuncContext* notExistsFunc();

  class  AggregateContext : public antlr4::ParserRuleContext {
  public:
    AggregateContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COUNT();
    antlr4::tree::TerminalNode *OPEN_BRACE();
    antlr4::tree::TerminalNode *CLOSE_BRACE();
    antlr4::tree::TerminalNode *SUM();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *MIN();
    antlr4::tree::TerminalNode *MAX();
    antlr4::tree::TerminalNode *AVG();
    antlr4::tree::TerminalNode *SAMPLE();
    antlr4::tree::TerminalNode *GROUP_CONCAT();
    antlr4::tree::TerminalNode *ASTERISK();
    antlr4::tree::TerminalNode *DISTINCT();
    antlr4::tree::TerminalNode *SEMICOLON();
    antlr4::tree::TerminalNode *SEPARATOR();
    antlr4::tree::TerminalNode *EQUAL();
    StringContext *string();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  AggregateContext* aggregate();

  class  IriRefOrFunctionContext : public antlr4::ParserRuleContext {
  public:
    IriRefOrFunctionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    IriRefContext *iriRef();
    ArgListContext *argList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IriRefOrFunctionContext* iriRefOrFunction();

  class  RdfLiteralContext : public antlr4::ParserRuleContext {
  public:
    RdfLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StringContext *string();
    antlr4::tree::TerminalNode *LANGTAG();
    antlr4::tree::TerminalNode *REFERENCE();
    IriRefContext *iriRef();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  RdfLiteralContext* rdfLiteral();

  class  NumericLiteralContext : public antlr4::ParserRuleContext {
  public:
    NumericLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    NumericLiteralUnsignedContext *numericLiteralUnsigned();
    NumericLiteralPositiveContext *numericLiteralPositive();
    NumericLiteralNegativeContext *numericLiteralNegative();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NumericLiteralContext* numericLiteral();

  class  NumericLiteralUnsignedContext : public antlr4::ParserRuleContext {
  public:
    NumericLiteralUnsignedContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INTEGER();
    antlr4::tree::TerminalNode *DECIMAL();
    antlr4::tree::TerminalNode *DOUBLE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NumericLiteralUnsignedContext* numericLiteralUnsigned();

  class  NumericLiteralPositiveContext : public antlr4::ParserRuleContext {
  public:
    NumericLiteralPositiveContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INTEGER_POSITIVE();
    antlr4::tree::TerminalNode *DECIMAL_POSITIVE();
    antlr4::tree::TerminalNode *DOUBLE_POSITIVE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NumericLiteralPositiveContext* numericLiteralPositive();

  class  NumericLiteralNegativeContext : public antlr4::ParserRuleContext {
  public:
    NumericLiteralNegativeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INTEGER_NEGATIVE();
    antlr4::tree::TerminalNode *DECIMAL_NEGATIVE();
    antlr4::tree::TerminalNode *DOUBLE_NEGATIVE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  NumericLiteralNegativeContext* numericLiteralNegative();

  class  BooleanLiteralContext : public antlr4::ParserRuleContext {
  public:
    BooleanLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TRUE();
    antlr4::tree::TerminalNode *FALSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BooleanLiteralContext* booleanLiteral();

  class  StringContext : public antlr4::ParserRuleContext {
  public:
    StringContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING_LITERAL1();
    antlr4::tree::TerminalNode *STRING_LITERAL2();
    antlr4::tree::TerminalNode *STRING_LITERAL_LONG1();
    antlr4::tree::TerminalNode *STRING_LITERAL_LONG2();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  StringContext* string();

  class  IriRefContext : public antlr4::ParserRuleContext {
  public:
    IriRefContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IRI_REF();
    PrefixedNameContext *prefixedName();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  IriRefContext* iriRef();

  class  PrefixedNameContext : public antlr4::ParserRuleContext {
  public:
    PrefixedNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PNAME_LN();
    antlr4::tree::TerminalNode *PNAME_NS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  PrefixedNameContext* prefixedName();

  class  BlankNodeContext : public antlr4::ParserRuleContext {
  public:
    BlankNodeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BLANK_NODE_LABEL();
    antlr4::tree::TerminalNode *OPEN_SQUARE_BRACE();
    antlr4::tree::TerminalNode *CLOSE_SQUARE_BRACE();
    std::vector<antlr4::tree::TerminalNode *> WS();
    antlr4::tree::TerminalNode* WS(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;
   
  };

  BlankNodeContext* blankNode();


private:
  static std::vector<antlr4::dfa::DFA> _decisionToDFA;
  static antlr4::atn::PredictionContextCache _sharedContextCache;
  static std::vector<std::string> _ruleNames;
  static std::vector<std::string> _tokenNames;

  static std::vector<std::string> _literalNames;
  static std::vector<std::string> _symbolicNames;
  static antlr4::dfa::Vocabulary _vocabulary;
  static antlr4::atn::ATN _atn;
  static std::vector<uint16_t> _serializedATN;


  struct Initializer {
    Initializer();
  };
  static Initializer _init;
};

