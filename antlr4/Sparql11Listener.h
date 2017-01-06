
// Generated from Sparql11.g4 by ANTLR 4.6

#pragma once


#include "antlr4-runtime.h"
#include "Sparql11Parser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by Sparql11Parser.
 */
class  Sparql11Listener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterQueryUnit(Sparql11Parser::QueryUnitContext *ctx) = 0;
  virtual void exitQueryUnit(Sparql11Parser::QueryUnitContext *ctx) = 0;

  virtual void enterQuery(Sparql11Parser::QueryContext *ctx) = 0;
  virtual void exitQuery(Sparql11Parser::QueryContext *ctx) = 0;

  virtual void enterPrologue(Sparql11Parser::PrologueContext *ctx) = 0;
  virtual void exitPrologue(Sparql11Parser::PrologueContext *ctx) = 0;

  virtual void enterBaseDecl(Sparql11Parser::BaseDeclContext *ctx) = 0;
  virtual void exitBaseDecl(Sparql11Parser::BaseDeclContext *ctx) = 0;

  virtual void enterPrefixDecl(Sparql11Parser::PrefixDeclContext *ctx) = 0;
  virtual void exitPrefixDecl(Sparql11Parser::PrefixDeclContext *ctx) = 0;

  virtual void enterSelectQuery(Sparql11Parser::SelectQueryContext *ctx) = 0;
  virtual void exitSelectQuery(Sparql11Parser::SelectQueryContext *ctx) = 0;

  virtual void enterSubSelect(Sparql11Parser::SubSelectContext *ctx) = 0;
  virtual void exitSubSelect(Sparql11Parser::SubSelectContext *ctx) = 0;

  virtual void enterSelectClause(Sparql11Parser::SelectClauseContext *ctx) = 0;
  virtual void exitSelectClause(Sparql11Parser::SelectClauseContext *ctx) = 0;

  virtual void enterConstructQuery(Sparql11Parser::ConstructQueryContext *ctx) = 0;
  virtual void exitConstructQuery(Sparql11Parser::ConstructQueryContext *ctx) = 0;

  virtual void enterDescribeQuery(Sparql11Parser::DescribeQueryContext *ctx) = 0;
  virtual void exitDescribeQuery(Sparql11Parser::DescribeQueryContext *ctx) = 0;

  virtual void enterAskQuery(Sparql11Parser::AskQueryContext *ctx) = 0;
  virtual void exitAskQuery(Sparql11Parser::AskQueryContext *ctx) = 0;

  virtual void enterDatasetClause(Sparql11Parser::DatasetClauseContext *ctx) = 0;
  virtual void exitDatasetClause(Sparql11Parser::DatasetClauseContext *ctx) = 0;

  virtual void enterDefaultGraphClause(Sparql11Parser::DefaultGraphClauseContext *ctx) = 0;
  virtual void exitDefaultGraphClause(Sparql11Parser::DefaultGraphClauseContext *ctx) = 0;

  virtual void enterNamedGraphClause(Sparql11Parser::NamedGraphClauseContext *ctx) = 0;
  virtual void exitNamedGraphClause(Sparql11Parser::NamedGraphClauseContext *ctx) = 0;

  virtual void enterSourceSelector(Sparql11Parser::SourceSelectorContext *ctx) = 0;
  virtual void exitSourceSelector(Sparql11Parser::SourceSelectorContext *ctx) = 0;

  virtual void enterWhereClause(Sparql11Parser::WhereClauseContext *ctx) = 0;
  virtual void exitWhereClause(Sparql11Parser::WhereClauseContext *ctx) = 0;

  virtual void enterSolutionModifier(Sparql11Parser::SolutionModifierContext *ctx) = 0;
  virtual void exitSolutionModifier(Sparql11Parser::SolutionModifierContext *ctx) = 0;

  virtual void enterGroupClause(Sparql11Parser::GroupClauseContext *ctx) = 0;
  virtual void exitGroupClause(Sparql11Parser::GroupClauseContext *ctx) = 0;

  virtual void enterGroupCondition(Sparql11Parser::GroupConditionContext *ctx) = 0;
  virtual void exitGroupCondition(Sparql11Parser::GroupConditionContext *ctx) = 0;

  virtual void enterHavingClause(Sparql11Parser::HavingClauseContext *ctx) = 0;
  virtual void exitHavingClause(Sparql11Parser::HavingClauseContext *ctx) = 0;

  virtual void enterHavingCondition(Sparql11Parser::HavingConditionContext *ctx) = 0;
  virtual void exitHavingCondition(Sparql11Parser::HavingConditionContext *ctx) = 0;

  virtual void enterOrderClause(Sparql11Parser::OrderClauseContext *ctx) = 0;
  virtual void exitOrderClause(Sparql11Parser::OrderClauseContext *ctx) = 0;

  virtual void enterOrderCondition(Sparql11Parser::OrderConditionContext *ctx) = 0;
  virtual void exitOrderCondition(Sparql11Parser::OrderConditionContext *ctx) = 0;

  virtual void enterLimitOffsetClauses(Sparql11Parser::LimitOffsetClausesContext *ctx) = 0;
  virtual void exitLimitOffsetClauses(Sparql11Parser::LimitOffsetClausesContext *ctx) = 0;

  virtual void enterLimitClause(Sparql11Parser::LimitClauseContext *ctx) = 0;
  virtual void exitLimitClause(Sparql11Parser::LimitClauseContext *ctx) = 0;

  virtual void enterOffsetClause(Sparql11Parser::OffsetClauseContext *ctx) = 0;
  virtual void exitOffsetClause(Sparql11Parser::OffsetClauseContext *ctx) = 0;

  virtual void enterBindingsClause(Sparql11Parser::BindingsClauseContext *ctx) = 0;
  virtual void exitBindingsClause(Sparql11Parser::BindingsClauseContext *ctx) = 0;

  virtual void enterBindingValue(Sparql11Parser::BindingValueContext *ctx) = 0;
  virtual void exitBindingValue(Sparql11Parser::BindingValueContext *ctx) = 0;

  virtual void enterUpdateUnit(Sparql11Parser::UpdateUnitContext *ctx) = 0;
  virtual void exitUpdateUnit(Sparql11Parser::UpdateUnitContext *ctx) = 0;

  virtual void enterUpdate(Sparql11Parser::UpdateContext *ctx) = 0;
  virtual void exitUpdate(Sparql11Parser::UpdateContext *ctx) = 0;

  virtual void enterUpdate1(Sparql11Parser::Update1Context *ctx) = 0;
  virtual void exitUpdate1(Sparql11Parser::Update1Context *ctx) = 0;

  virtual void enterLoad(Sparql11Parser::LoadContext *ctx) = 0;
  virtual void exitLoad(Sparql11Parser::LoadContext *ctx) = 0;

  virtual void enterClear(Sparql11Parser::ClearContext *ctx) = 0;
  virtual void exitClear(Sparql11Parser::ClearContext *ctx) = 0;

  virtual void enterDrop(Sparql11Parser::DropContext *ctx) = 0;
  virtual void exitDrop(Sparql11Parser::DropContext *ctx) = 0;

  virtual void enterCreate(Sparql11Parser::CreateContext *ctx) = 0;
  virtual void exitCreate(Sparql11Parser::CreateContext *ctx) = 0;

  virtual void enterInsertData(Sparql11Parser::InsertDataContext *ctx) = 0;
  virtual void exitInsertData(Sparql11Parser::InsertDataContext *ctx) = 0;

  virtual void enterDeleteData(Sparql11Parser::DeleteDataContext *ctx) = 0;
  virtual void exitDeleteData(Sparql11Parser::DeleteDataContext *ctx) = 0;

  virtual void enterDeleteWhere(Sparql11Parser::DeleteWhereContext *ctx) = 0;
  virtual void exitDeleteWhere(Sparql11Parser::DeleteWhereContext *ctx) = 0;

  virtual void enterModify(Sparql11Parser::ModifyContext *ctx) = 0;
  virtual void exitModify(Sparql11Parser::ModifyContext *ctx) = 0;

  virtual void enterDeleteClause(Sparql11Parser::DeleteClauseContext *ctx) = 0;
  virtual void exitDeleteClause(Sparql11Parser::DeleteClauseContext *ctx) = 0;

  virtual void enterInsertClause(Sparql11Parser::InsertClauseContext *ctx) = 0;
  virtual void exitInsertClause(Sparql11Parser::InsertClauseContext *ctx) = 0;

  virtual void enterUsingClause(Sparql11Parser::UsingClauseContext *ctx) = 0;
  virtual void exitUsingClause(Sparql11Parser::UsingClauseContext *ctx) = 0;

  virtual void enterGraphRef(Sparql11Parser::GraphRefContext *ctx) = 0;
  virtual void exitGraphRef(Sparql11Parser::GraphRefContext *ctx) = 0;

  virtual void enterGraphRefAll(Sparql11Parser::GraphRefAllContext *ctx) = 0;
  virtual void exitGraphRefAll(Sparql11Parser::GraphRefAllContext *ctx) = 0;

  virtual void enterQuadPattern(Sparql11Parser::QuadPatternContext *ctx) = 0;
  virtual void exitQuadPattern(Sparql11Parser::QuadPatternContext *ctx) = 0;

  virtual void enterQuadData(Sparql11Parser::QuadDataContext *ctx) = 0;
  virtual void exitQuadData(Sparql11Parser::QuadDataContext *ctx) = 0;

  virtual void enterQuads(Sparql11Parser::QuadsContext *ctx) = 0;
  virtual void exitQuads(Sparql11Parser::QuadsContext *ctx) = 0;

  virtual void enterQuadsNotTriples(Sparql11Parser::QuadsNotTriplesContext *ctx) = 0;
  virtual void exitQuadsNotTriples(Sparql11Parser::QuadsNotTriplesContext *ctx) = 0;

  virtual void enterTriplesTemplate(Sparql11Parser::TriplesTemplateContext *ctx) = 0;
  virtual void exitTriplesTemplate(Sparql11Parser::TriplesTemplateContext *ctx) = 0;

  virtual void enterGroupGraphPattern(Sparql11Parser::GroupGraphPatternContext *ctx) = 0;
  virtual void exitGroupGraphPattern(Sparql11Parser::GroupGraphPatternContext *ctx) = 0;

  virtual void enterGroupGraphPatternSub(Sparql11Parser::GroupGraphPatternSubContext *ctx) = 0;
  virtual void exitGroupGraphPatternSub(Sparql11Parser::GroupGraphPatternSubContext *ctx) = 0;

  virtual void enterTriplesBlock(Sparql11Parser::TriplesBlockContext *ctx) = 0;
  virtual void exitTriplesBlock(Sparql11Parser::TriplesBlockContext *ctx) = 0;

  virtual void enterGraphPatternNotTriples(Sparql11Parser::GraphPatternNotTriplesContext *ctx) = 0;
  virtual void exitGraphPatternNotTriples(Sparql11Parser::GraphPatternNotTriplesContext *ctx) = 0;

  virtual void enterOptionalGraphPattern(Sparql11Parser::OptionalGraphPatternContext *ctx) = 0;
  virtual void exitOptionalGraphPattern(Sparql11Parser::OptionalGraphPatternContext *ctx) = 0;

  virtual void enterGraphGraphPattern(Sparql11Parser::GraphGraphPatternContext *ctx) = 0;
  virtual void exitGraphGraphPattern(Sparql11Parser::GraphGraphPatternContext *ctx) = 0;

  virtual void enterServiceGraphPattern(Sparql11Parser::ServiceGraphPatternContext *ctx) = 0;
  virtual void exitServiceGraphPattern(Sparql11Parser::ServiceGraphPatternContext *ctx) = 0;

  virtual void enterMinusGraphPattern(Sparql11Parser::MinusGraphPatternContext *ctx) = 0;
  virtual void exitMinusGraphPattern(Sparql11Parser::MinusGraphPatternContext *ctx) = 0;

  virtual void enterGroupOrUnionGraphPattern(Sparql11Parser::GroupOrUnionGraphPatternContext *ctx) = 0;
  virtual void exitGroupOrUnionGraphPattern(Sparql11Parser::GroupOrUnionGraphPatternContext *ctx) = 0;

  virtual void enterFilter(Sparql11Parser::FilterContext *ctx) = 0;
  virtual void exitFilter(Sparql11Parser::FilterContext *ctx) = 0;

  virtual void enterConstraint(Sparql11Parser::ConstraintContext *ctx) = 0;
  virtual void exitConstraint(Sparql11Parser::ConstraintContext *ctx) = 0;

  virtual void enterFunctionCall(Sparql11Parser::FunctionCallContext *ctx) = 0;
  virtual void exitFunctionCall(Sparql11Parser::FunctionCallContext *ctx) = 0;

  virtual void enterArgList(Sparql11Parser::ArgListContext *ctx) = 0;
  virtual void exitArgList(Sparql11Parser::ArgListContext *ctx) = 0;

  virtual void enterExpressionList(Sparql11Parser::ExpressionListContext *ctx) = 0;
  virtual void exitExpressionList(Sparql11Parser::ExpressionListContext *ctx) = 0;

  virtual void enterConstructTemplate(Sparql11Parser::ConstructTemplateContext *ctx) = 0;
  virtual void exitConstructTemplate(Sparql11Parser::ConstructTemplateContext *ctx) = 0;

  virtual void enterConstructTriples(Sparql11Parser::ConstructTriplesContext *ctx) = 0;
  virtual void exitConstructTriples(Sparql11Parser::ConstructTriplesContext *ctx) = 0;

  virtual void enterTriplesSameSubject(Sparql11Parser::TriplesSameSubjectContext *ctx) = 0;
  virtual void exitTriplesSameSubject(Sparql11Parser::TriplesSameSubjectContext *ctx) = 0;

  virtual void enterPropertyListNotEmpty(Sparql11Parser::PropertyListNotEmptyContext *ctx) = 0;
  virtual void exitPropertyListNotEmpty(Sparql11Parser::PropertyListNotEmptyContext *ctx) = 0;

  virtual void enterPropertyList(Sparql11Parser::PropertyListContext *ctx) = 0;
  virtual void exitPropertyList(Sparql11Parser::PropertyListContext *ctx) = 0;

  virtual void enterObjectList(Sparql11Parser::ObjectListContext *ctx) = 0;
  virtual void exitObjectList(Sparql11Parser::ObjectListContext *ctx) = 0;

  virtual void enterObject(Sparql11Parser::ObjectContext *ctx) = 0;
  virtual void exitObject(Sparql11Parser::ObjectContext *ctx) = 0;

  virtual void enterVerb(Sparql11Parser::VerbContext *ctx) = 0;
  virtual void exitVerb(Sparql11Parser::VerbContext *ctx) = 0;

  virtual void enterTriplesSameSubjectPath(Sparql11Parser::TriplesSameSubjectPathContext *ctx) = 0;
  virtual void exitTriplesSameSubjectPath(Sparql11Parser::TriplesSameSubjectPathContext *ctx) = 0;

  virtual void enterPropertyListNotEmptyPath(Sparql11Parser::PropertyListNotEmptyPathContext *ctx) = 0;
  virtual void exitPropertyListNotEmptyPath(Sparql11Parser::PropertyListNotEmptyPathContext *ctx) = 0;

  virtual void enterPropertyListPath(Sparql11Parser::PropertyListPathContext *ctx) = 0;
  virtual void exitPropertyListPath(Sparql11Parser::PropertyListPathContext *ctx) = 0;

  virtual void enterVerbPath(Sparql11Parser::VerbPathContext *ctx) = 0;
  virtual void exitVerbPath(Sparql11Parser::VerbPathContext *ctx) = 0;

  virtual void enterVerbSimple(Sparql11Parser::VerbSimpleContext *ctx) = 0;
  virtual void exitVerbSimple(Sparql11Parser::VerbSimpleContext *ctx) = 0;

  virtual void enterPath(Sparql11Parser::PathContext *ctx) = 0;
  virtual void exitPath(Sparql11Parser::PathContext *ctx) = 0;

  virtual void enterPathAlternative(Sparql11Parser::PathAlternativeContext *ctx) = 0;
  virtual void exitPathAlternative(Sparql11Parser::PathAlternativeContext *ctx) = 0;

  virtual void enterPathSequence(Sparql11Parser::PathSequenceContext *ctx) = 0;
  virtual void exitPathSequence(Sparql11Parser::PathSequenceContext *ctx) = 0;

  virtual void enterPathElt(Sparql11Parser::PathEltContext *ctx) = 0;
  virtual void exitPathElt(Sparql11Parser::PathEltContext *ctx) = 0;

  virtual void enterPathEltOrInverse(Sparql11Parser::PathEltOrInverseContext *ctx) = 0;
  virtual void exitPathEltOrInverse(Sparql11Parser::PathEltOrInverseContext *ctx) = 0;

  virtual void enterPathMod(Sparql11Parser::PathModContext *ctx) = 0;
  virtual void exitPathMod(Sparql11Parser::PathModContext *ctx) = 0;

  virtual void enterPathPrimary(Sparql11Parser::PathPrimaryContext *ctx) = 0;
  virtual void exitPathPrimary(Sparql11Parser::PathPrimaryContext *ctx) = 0;

  virtual void enterPathNegatedPropertySet(Sparql11Parser::PathNegatedPropertySetContext *ctx) = 0;
  virtual void exitPathNegatedPropertySet(Sparql11Parser::PathNegatedPropertySetContext *ctx) = 0;

  virtual void enterPathOneInPropertySet(Sparql11Parser::PathOneInPropertySetContext *ctx) = 0;
  virtual void exitPathOneInPropertySet(Sparql11Parser::PathOneInPropertySetContext *ctx) = 0;

  virtual void enterInteger(Sparql11Parser::IntegerContext *ctx) = 0;
  virtual void exitInteger(Sparql11Parser::IntegerContext *ctx) = 0;

  virtual void enterTriplesNode(Sparql11Parser::TriplesNodeContext *ctx) = 0;
  virtual void exitTriplesNode(Sparql11Parser::TriplesNodeContext *ctx) = 0;

  virtual void enterBlankNodePropertyList(Sparql11Parser::BlankNodePropertyListContext *ctx) = 0;
  virtual void exitBlankNodePropertyList(Sparql11Parser::BlankNodePropertyListContext *ctx) = 0;

  virtual void enterCollection(Sparql11Parser::CollectionContext *ctx) = 0;
  virtual void exitCollection(Sparql11Parser::CollectionContext *ctx) = 0;

  virtual void enterGraphNode(Sparql11Parser::GraphNodeContext *ctx) = 0;
  virtual void exitGraphNode(Sparql11Parser::GraphNodeContext *ctx) = 0;

  virtual void enterVarOrTerm(Sparql11Parser::VarOrTermContext *ctx) = 0;
  virtual void exitVarOrTerm(Sparql11Parser::VarOrTermContext *ctx) = 0;

  virtual void enterVarOrIriRef(Sparql11Parser::VarOrIriRefContext *ctx) = 0;
  virtual void exitVarOrIriRef(Sparql11Parser::VarOrIriRefContext *ctx) = 0;

  virtual void enterVariable(Sparql11Parser::VariableContext *ctx) = 0;
  virtual void exitVariable(Sparql11Parser::VariableContext *ctx) = 0;

  virtual void enterGraphTerm(Sparql11Parser::GraphTermContext *ctx) = 0;
  virtual void exitGraphTerm(Sparql11Parser::GraphTermContext *ctx) = 0;

  virtual void enterExpression(Sparql11Parser::ExpressionContext *ctx) = 0;
  virtual void exitExpression(Sparql11Parser::ExpressionContext *ctx) = 0;

  virtual void enterConditionalOrExpression(Sparql11Parser::ConditionalOrExpressionContext *ctx) = 0;
  virtual void exitConditionalOrExpression(Sparql11Parser::ConditionalOrExpressionContext *ctx) = 0;

  virtual void enterConditionalAndExpression(Sparql11Parser::ConditionalAndExpressionContext *ctx) = 0;
  virtual void exitConditionalAndExpression(Sparql11Parser::ConditionalAndExpressionContext *ctx) = 0;

  virtual void enterValueLogical(Sparql11Parser::ValueLogicalContext *ctx) = 0;
  virtual void exitValueLogical(Sparql11Parser::ValueLogicalContext *ctx) = 0;

  virtual void enterRelationalExpression(Sparql11Parser::RelationalExpressionContext *ctx) = 0;
  virtual void exitRelationalExpression(Sparql11Parser::RelationalExpressionContext *ctx) = 0;

  virtual void enterNumericExpression(Sparql11Parser::NumericExpressionContext *ctx) = 0;
  virtual void exitNumericExpression(Sparql11Parser::NumericExpressionContext *ctx) = 0;

  virtual void enterAdditiveExpression(Sparql11Parser::AdditiveExpressionContext *ctx) = 0;
  virtual void exitAdditiveExpression(Sparql11Parser::AdditiveExpressionContext *ctx) = 0;

  virtual void enterMultiplicativeExpression(Sparql11Parser::MultiplicativeExpressionContext *ctx) = 0;
  virtual void exitMultiplicativeExpression(Sparql11Parser::MultiplicativeExpressionContext *ctx) = 0;

  virtual void enterUnaryExpression(Sparql11Parser::UnaryExpressionContext *ctx) = 0;
  virtual void exitUnaryExpression(Sparql11Parser::UnaryExpressionContext *ctx) = 0;

  virtual void enterPrimaryExpression(Sparql11Parser::PrimaryExpressionContext *ctx) = 0;
  virtual void exitPrimaryExpression(Sparql11Parser::PrimaryExpressionContext *ctx) = 0;

  virtual void enterBrackettedExpression(Sparql11Parser::BrackettedExpressionContext *ctx) = 0;
  virtual void exitBrackettedExpression(Sparql11Parser::BrackettedExpressionContext *ctx) = 0;

  virtual void enterBuiltInCall(Sparql11Parser::BuiltInCallContext *ctx) = 0;
  virtual void exitBuiltInCall(Sparql11Parser::BuiltInCallContext *ctx) = 0;

  virtual void enterRegexExpression(Sparql11Parser::RegexExpressionContext *ctx) = 0;
  virtual void exitRegexExpression(Sparql11Parser::RegexExpressionContext *ctx) = 0;

  virtual void enterExistsFunc(Sparql11Parser::ExistsFuncContext *ctx) = 0;
  virtual void exitExistsFunc(Sparql11Parser::ExistsFuncContext *ctx) = 0;

  virtual void enterNotExistsFunc(Sparql11Parser::NotExistsFuncContext *ctx) = 0;
  virtual void exitNotExistsFunc(Sparql11Parser::NotExistsFuncContext *ctx) = 0;

  virtual void enterAggregate(Sparql11Parser::AggregateContext *ctx) = 0;
  virtual void exitAggregate(Sparql11Parser::AggregateContext *ctx) = 0;

  virtual void enterIriRefOrFunction(Sparql11Parser::IriRefOrFunctionContext *ctx) = 0;
  virtual void exitIriRefOrFunction(Sparql11Parser::IriRefOrFunctionContext *ctx) = 0;

  virtual void enterRdfLiteral(Sparql11Parser::RdfLiteralContext *ctx) = 0;
  virtual void exitRdfLiteral(Sparql11Parser::RdfLiteralContext *ctx) = 0;

  virtual void enterNumericLiteral(Sparql11Parser::NumericLiteralContext *ctx) = 0;
  virtual void exitNumericLiteral(Sparql11Parser::NumericLiteralContext *ctx) = 0;

  virtual void enterNumericLiteralUnsigned(Sparql11Parser::NumericLiteralUnsignedContext *ctx) = 0;
  virtual void exitNumericLiteralUnsigned(Sparql11Parser::NumericLiteralUnsignedContext *ctx) = 0;

  virtual void enterNumericLiteralPositive(Sparql11Parser::NumericLiteralPositiveContext *ctx) = 0;
  virtual void exitNumericLiteralPositive(Sparql11Parser::NumericLiteralPositiveContext *ctx) = 0;

  virtual void enterNumericLiteralNegative(Sparql11Parser::NumericLiteralNegativeContext *ctx) = 0;
  virtual void exitNumericLiteralNegative(Sparql11Parser::NumericLiteralNegativeContext *ctx) = 0;

  virtual void enterBooleanLiteral(Sparql11Parser::BooleanLiteralContext *ctx) = 0;
  virtual void exitBooleanLiteral(Sparql11Parser::BooleanLiteralContext *ctx) = 0;

  virtual void enterString(Sparql11Parser::StringContext *ctx) = 0;
  virtual void exitString(Sparql11Parser::StringContext *ctx) = 0;

  virtual void enterIriRef(Sparql11Parser::IriRefContext *ctx) = 0;
  virtual void exitIriRef(Sparql11Parser::IriRefContext *ctx) = 0;

  virtual void enterPrefixedName(Sparql11Parser::PrefixedNameContext *ctx) = 0;
  virtual void exitPrefixedName(Sparql11Parser::PrefixedNameContext *ctx) = 0;

  virtual void enterBlankNode(Sparql11Parser::BlankNodeContext *ctx) = 0;
  virtual void exitBlankNode(Sparql11Parser::BlankNodeContext *ctx) = 0;


};

