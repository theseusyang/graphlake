
// Generated from Sparql11.g4 by ANTLR 4.6

#pragma once


#include "antlr4-runtime.h"
#include "Sparql11Listener.h"


/**
 * This class provides an empty implementation of Sparql11Listener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  Sparql11BaseListener : public Sparql11Listener {
public:

  virtual void enterQueryUnit(Sparql11Parser::QueryUnitContext * /*ctx*/) override { }
  virtual void exitQueryUnit(Sparql11Parser::QueryUnitContext * /*ctx*/) override { }

  virtual void enterQuery(Sparql11Parser::QueryContext * /*ctx*/) override { }
  virtual void exitQuery(Sparql11Parser::QueryContext * /*ctx*/) override { }

  virtual void enterPrologue(Sparql11Parser::PrologueContext * /*ctx*/) override { }
  virtual void exitPrologue(Sparql11Parser::PrologueContext * /*ctx*/) override { }

  virtual void enterBaseDecl(Sparql11Parser::BaseDeclContext * /*ctx*/) override { }
  virtual void exitBaseDecl(Sparql11Parser::BaseDeclContext * /*ctx*/) override { }

  virtual void enterPrefixDecl(Sparql11Parser::PrefixDeclContext * /*ctx*/) override { }
  virtual void exitPrefixDecl(Sparql11Parser::PrefixDeclContext * /*ctx*/) override { }

  virtual void enterSelectQuery(Sparql11Parser::SelectQueryContext * /*ctx*/) override { }
  virtual void exitSelectQuery(Sparql11Parser::SelectQueryContext * /*ctx*/) override { }

  virtual void enterSubSelect(Sparql11Parser::SubSelectContext * /*ctx*/) override { }
  virtual void exitSubSelect(Sparql11Parser::SubSelectContext * /*ctx*/) override { }

  virtual void enterSelectClause(Sparql11Parser::SelectClauseContext * /*ctx*/) override { }
  virtual void exitSelectClause(Sparql11Parser::SelectClauseContext * /*ctx*/) override { }

  virtual void enterConstructQuery(Sparql11Parser::ConstructQueryContext * /*ctx*/) override { }
  virtual void exitConstructQuery(Sparql11Parser::ConstructQueryContext * /*ctx*/) override { }

  virtual void enterDescribeQuery(Sparql11Parser::DescribeQueryContext * /*ctx*/) override { }
  virtual void exitDescribeQuery(Sparql11Parser::DescribeQueryContext * /*ctx*/) override { }

  virtual void enterAskQuery(Sparql11Parser::AskQueryContext * /*ctx*/) override { }
  virtual void exitAskQuery(Sparql11Parser::AskQueryContext * /*ctx*/) override { }

  virtual void enterDatasetClause(Sparql11Parser::DatasetClauseContext * /*ctx*/) override { }
  virtual void exitDatasetClause(Sparql11Parser::DatasetClauseContext * /*ctx*/) override { }

  virtual void enterDefaultGraphClause(Sparql11Parser::DefaultGraphClauseContext * /*ctx*/) override { }
  virtual void exitDefaultGraphClause(Sparql11Parser::DefaultGraphClauseContext * /*ctx*/) override { }

  virtual void enterNamedGraphClause(Sparql11Parser::NamedGraphClauseContext * /*ctx*/) override { }
  virtual void exitNamedGraphClause(Sparql11Parser::NamedGraphClauseContext * /*ctx*/) override { }

  virtual void enterSourceSelector(Sparql11Parser::SourceSelectorContext * /*ctx*/) override { }
  virtual void exitSourceSelector(Sparql11Parser::SourceSelectorContext * /*ctx*/) override { }

  virtual void enterWhereClause(Sparql11Parser::WhereClauseContext * /*ctx*/) override { }
  virtual void exitWhereClause(Sparql11Parser::WhereClauseContext * /*ctx*/) override { }

  virtual void enterSolutionModifier(Sparql11Parser::SolutionModifierContext * /*ctx*/) override { }
  virtual void exitSolutionModifier(Sparql11Parser::SolutionModifierContext * /*ctx*/) override { }

  virtual void enterGroupClause(Sparql11Parser::GroupClauseContext * /*ctx*/) override { }
  virtual void exitGroupClause(Sparql11Parser::GroupClauseContext * /*ctx*/) override { }

  virtual void enterGroupCondition(Sparql11Parser::GroupConditionContext * /*ctx*/) override { }
  virtual void exitGroupCondition(Sparql11Parser::GroupConditionContext * /*ctx*/) override { }

  virtual void enterHavingClause(Sparql11Parser::HavingClauseContext * /*ctx*/) override { }
  virtual void exitHavingClause(Sparql11Parser::HavingClauseContext * /*ctx*/) override { }

  virtual void enterHavingCondition(Sparql11Parser::HavingConditionContext * /*ctx*/) override { }
  virtual void exitHavingCondition(Sparql11Parser::HavingConditionContext * /*ctx*/) override { }

  virtual void enterOrderClause(Sparql11Parser::OrderClauseContext * /*ctx*/) override { }
  virtual void exitOrderClause(Sparql11Parser::OrderClauseContext * /*ctx*/) override { }

  virtual void enterOrderCondition(Sparql11Parser::OrderConditionContext * /*ctx*/) override { }
  virtual void exitOrderCondition(Sparql11Parser::OrderConditionContext * /*ctx*/) override { }

  virtual void enterLimitOffsetClauses(Sparql11Parser::LimitOffsetClausesContext * /*ctx*/) override { }
  virtual void exitLimitOffsetClauses(Sparql11Parser::LimitOffsetClausesContext * /*ctx*/) override { }

  virtual void enterLimitClause(Sparql11Parser::LimitClauseContext * /*ctx*/) override { }
  virtual void exitLimitClause(Sparql11Parser::LimitClauseContext * /*ctx*/) override { }

  virtual void enterOffsetClause(Sparql11Parser::OffsetClauseContext * /*ctx*/) override { }
  virtual void exitOffsetClause(Sparql11Parser::OffsetClauseContext * /*ctx*/) override { }

  virtual void enterBindingsClause(Sparql11Parser::BindingsClauseContext * /*ctx*/) override { }
  virtual void exitBindingsClause(Sparql11Parser::BindingsClauseContext * /*ctx*/) override { }

  virtual void enterBindingValue(Sparql11Parser::BindingValueContext * /*ctx*/) override { }
  virtual void exitBindingValue(Sparql11Parser::BindingValueContext * /*ctx*/) override { }

  virtual void enterUpdateUnit(Sparql11Parser::UpdateUnitContext * /*ctx*/) override { }
  virtual void exitUpdateUnit(Sparql11Parser::UpdateUnitContext * /*ctx*/) override { }

  virtual void enterUpdate(Sparql11Parser::UpdateContext * /*ctx*/) override { }
  virtual void exitUpdate(Sparql11Parser::UpdateContext * /*ctx*/) override { }

  virtual void enterUpdate1(Sparql11Parser::Update1Context * /*ctx*/) override { }
  virtual void exitUpdate1(Sparql11Parser::Update1Context * /*ctx*/) override { }

  virtual void enterLoad(Sparql11Parser::LoadContext * /*ctx*/) override { }
  virtual void exitLoad(Sparql11Parser::LoadContext * /*ctx*/) override { }

  virtual void enterClear(Sparql11Parser::ClearContext * /*ctx*/) override { }
  virtual void exitClear(Sparql11Parser::ClearContext * /*ctx*/) override { }

  virtual void enterDrop(Sparql11Parser::DropContext * /*ctx*/) override { }
  virtual void exitDrop(Sparql11Parser::DropContext * /*ctx*/) override { }

  virtual void enterCreate(Sparql11Parser::CreateContext * /*ctx*/) override { }
  virtual void exitCreate(Sparql11Parser::CreateContext * /*ctx*/) override { }

  virtual void enterInsertData(Sparql11Parser::InsertDataContext * /*ctx*/) override { }
  virtual void exitInsertData(Sparql11Parser::InsertDataContext * /*ctx*/) override { }

  virtual void enterDeleteData(Sparql11Parser::DeleteDataContext * /*ctx*/) override { }
  virtual void exitDeleteData(Sparql11Parser::DeleteDataContext * /*ctx*/) override { }

  virtual void enterDeleteWhere(Sparql11Parser::DeleteWhereContext * /*ctx*/) override { }
  virtual void exitDeleteWhere(Sparql11Parser::DeleteWhereContext * /*ctx*/) override { }

  virtual void enterModify(Sparql11Parser::ModifyContext * /*ctx*/) override { }
  virtual void exitModify(Sparql11Parser::ModifyContext * /*ctx*/) override { }

  virtual void enterDeleteClause(Sparql11Parser::DeleteClauseContext * /*ctx*/) override { }
  virtual void exitDeleteClause(Sparql11Parser::DeleteClauseContext * /*ctx*/) override { }

  virtual void enterInsertClause(Sparql11Parser::InsertClauseContext * /*ctx*/) override { }
  virtual void exitInsertClause(Sparql11Parser::InsertClauseContext * /*ctx*/) override { }

  virtual void enterUsingClause(Sparql11Parser::UsingClauseContext * /*ctx*/) override { }
  virtual void exitUsingClause(Sparql11Parser::UsingClauseContext * /*ctx*/) override { }

  virtual void enterGraphRef(Sparql11Parser::GraphRefContext * /*ctx*/) override { }
  virtual void exitGraphRef(Sparql11Parser::GraphRefContext * /*ctx*/) override { }

  virtual void enterGraphRefAll(Sparql11Parser::GraphRefAllContext * /*ctx*/) override { }
  virtual void exitGraphRefAll(Sparql11Parser::GraphRefAllContext * /*ctx*/) override { }

  virtual void enterQuadPattern(Sparql11Parser::QuadPatternContext * /*ctx*/) override { }
  virtual void exitQuadPattern(Sparql11Parser::QuadPatternContext * /*ctx*/) override { }

  virtual void enterQuadData(Sparql11Parser::QuadDataContext * /*ctx*/) override { }
  virtual void exitQuadData(Sparql11Parser::QuadDataContext * /*ctx*/) override { }

  virtual void enterQuads(Sparql11Parser::QuadsContext * /*ctx*/) override { }
  virtual void exitQuads(Sparql11Parser::QuadsContext * /*ctx*/) override { }

  virtual void enterQuadsNotTriples(Sparql11Parser::QuadsNotTriplesContext * /*ctx*/) override { }
  virtual void exitQuadsNotTriples(Sparql11Parser::QuadsNotTriplesContext * /*ctx*/) override { }

  virtual void enterTriplesTemplate(Sparql11Parser::TriplesTemplateContext * /*ctx*/) override { }
  virtual void exitTriplesTemplate(Sparql11Parser::TriplesTemplateContext * /*ctx*/) override { }

  virtual void enterGroupGraphPattern(Sparql11Parser::GroupGraphPatternContext * /*ctx*/) override { }
  virtual void exitGroupGraphPattern(Sparql11Parser::GroupGraphPatternContext * /*ctx*/) override { }

  virtual void enterGroupGraphPatternSub(Sparql11Parser::GroupGraphPatternSubContext * /*ctx*/) override { }
  virtual void exitGroupGraphPatternSub(Sparql11Parser::GroupGraphPatternSubContext * /*ctx*/) override { }

  virtual void enterTriplesBlock(Sparql11Parser::TriplesBlockContext * /*ctx*/) override { }
  virtual void exitTriplesBlock(Sparql11Parser::TriplesBlockContext * /*ctx*/) override { }

  virtual void enterGraphPatternNotTriples(Sparql11Parser::GraphPatternNotTriplesContext * /*ctx*/) override { }
  virtual void exitGraphPatternNotTriples(Sparql11Parser::GraphPatternNotTriplesContext * /*ctx*/) override { }

  virtual void enterOptionalGraphPattern(Sparql11Parser::OptionalGraphPatternContext * /*ctx*/) override { }
  virtual void exitOptionalGraphPattern(Sparql11Parser::OptionalGraphPatternContext * /*ctx*/) override { }

  virtual void enterGraphGraphPattern(Sparql11Parser::GraphGraphPatternContext * /*ctx*/) override { }
  virtual void exitGraphGraphPattern(Sparql11Parser::GraphGraphPatternContext * /*ctx*/) override { }

  virtual void enterServiceGraphPattern(Sparql11Parser::ServiceGraphPatternContext * /*ctx*/) override { }
  virtual void exitServiceGraphPattern(Sparql11Parser::ServiceGraphPatternContext * /*ctx*/) override { }

  virtual void enterMinusGraphPattern(Sparql11Parser::MinusGraphPatternContext * /*ctx*/) override { }
  virtual void exitMinusGraphPattern(Sparql11Parser::MinusGraphPatternContext * /*ctx*/) override { }

  virtual void enterGroupOrUnionGraphPattern(Sparql11Parser::GroupOrUnionGraphPatternContext * /*ctx*/) override { }
  virtual void exitGroupOrUnionGraphPattern(Sparql11Parser::GroupOrUnionGraphPatternContext * /*ctx*/) override { }

  virtual void enterFilter(Sparql11Parser::FilterContext * /*ctx*/) override { }
  virtual void exitFilter(Sparql11Parser::FilterContext * /*ctx*/) override { }

  virtual void enterConstraint(Sparql11Parser::ConstraintContext * /*ctx*/) override { }
  virtual void exitConstraint(Sparql11Parser::ConstraintContext * /*ctx*/) override { }

  virtual void enterFunctionCall(Sparql11Parser::FunctionCallContext * /*ctx*/) override { }
  virtual void exitFunctionCall(Sparql11Parser::FunctionCallContext * /*ctx*/) override { }

  virtual void enterArgList(Sparql11Parser::ArgListContext * /*ctx*/) override { }
  virtual void exitArgList(Sparql11Parser::ArgListContext * /*ctx*/) override { }

  virtual void enterExpressionList(Sparql11Parser::ExpressionListContext * /*ctx*/) override { }
  virtual void exitExpressionList(Sparql11Parser::ExpressionListContext * /*ctx*/) override { }

  virtual void enterConstructTemplate(Sparql11Parser::ConstructTemplateContext * /*ctx*/) override { }
  virtual void exitConstructTemplate(Sparql11Parser::ConstructTemplateContext * /*ctx*/) override { }

  virtual void enterConstructTriples(Sparql11Parser::ConstructTriplesContext * /*ctx*/) override { }
  virtual void exitConstructTriples(Sparql11Parser::ConstructTriplesContext * /*ctx*/) override { }

  virtual void enterTriplesSameSubject(Sparql11Parser::TriplesSameSubjectContext * /*ctx*/) override { }
  virtual void exitTriplesSameSubject(Sparql11Parser::TriplesSameSubjectContext * /*ctx*/) override { }

  virtual void enterPropertyListNotEmpty(Sparql11Parser::PropertyListNotEmptyContext * /*ctx*/) override { }
  virtual void exitPropertyListNotEmpty(Sparql11Parser::PropertyListNotEmptyContext * /*ctx*/) override { }

  virtual void enterPropertyList(Sparql11Parser::PropertyListContext * /*ctx*/) override { }
  virtual void exitPropertyList(Sparql11Parser::PropertyListContext * /*ctx*/) override { }

  virtual void enterObjectList(Sparql11Parser::ObjectListContext * /*ctx*/) override { }
  virtual void exitObjectList(Sparql11Parser::ObjectListContext * /*ctx*/) override { }

  virtual void enterObject(Sparql11Parser::ObjectContext * /*ctx*/) override { }
  virtual void exitObject(Sparql11Parser::ObjectContext * /*ctx*/) override { }

  virtual void enterVerb(Sparql11Parser::VerbContext * /*ctx*/) override { }
  virtual void exitVerb(Sparql11Parser::VerbContext * /*ctx*/) override { }

  virtual void enterTriplesSameSubjectPath(Sparql11Parser::TriplesSameSubjectPathContext * /*ctx*/) override { }
  virtual void exitTriplesSameSubjectPath(Sparql11Parser::TriplesSameSubjectPathContext * /*ctx*/) override { }

  virtual void enterPropertyListNotEmptyPath(Sparql11Parser::PropertyListNotEmptyPathContext * /*ctx*/) override { }
  virtual void exitPropertyListNotEmptyPath(Sparql11Parser::PropertyListNotEmptyPathContext * /*ctx*/) override { }

  virtual void enterPropertyListPath(Sparql11Parser::PropertyListPathContext * /*ctx*/) override { }
  virtual void exitPropertyListPath(Sparql11Parser::PropertyListPathContext * /*ctx*/) override { }

  virtual void enterVerbPath(Sparql11Parser::VerbPathContext * /*ctx*/) override { }
  virtual void exitVerbPath(Sparql11Parser::VerbPathContext * /*ctx*/) override { }

  virtual void enterVerbSimple(Sparql11Parser::VerbSimpleContext * /*ctx*/) override { }
  virtual void exitVerbSimple(Sparql11Parser::VerbSimpleContext * /*ctx*/) override { }

  virtual void enterPath(Sparql11Parser::PathContext * /*ctx*/) override { }
  virtual void exitPath(Sparql11Parser::PathContext * /*ctx*/) override { }

  virtual void enterPathAlternative(Sparql11Parser::PathAlternativeContext * /*ctx*/) override { }
  virtual void exitPathAlternative(Sparql11Parser::PathAlternativeContext * /*ctx*/) override { }

  virtual void enterPathSequence(Sparql11Parser::PathSequenceContext * /*ctx*/) override { }
  virtual void exitPathSequence(Sparql11Parser::PathSequenceContext * /*ctx*/) override { }

  virtual void enterPathElt(Sparql11Parser::PathEltContext * /*ctx*/) override { }
  virtual void exitPathElt(Sparql11Parser::PathEltContext * /*ctx*/) override { }

  virtual void enterPathEltOrInverse(Sparql11Parser::PathEltOrInverseContext * /*ctx*/) override { }
  virtual void exitPathEltOrInverse(Sparql11Parser::PathEltOrInverseContext * /*ctx*/) override { }

  virtual void enterPathMod(Sparql11Parser::PathModContext * /*ctx*/) override { }
  virtual void exitPathMod(Sparql11Parser::PathModContext * /*ctx*/) override { }

  virtual void enterPathPrimary(Sparql11Parser::PathPrimaryContext * /*ctx*/) override { }
  virtual void exitPathPrimary(Sparql11Parser::PathPrimaryContext * /*ctx*/) override { }

  virtual void enterPathNegatedPropertySet(Sparql11Parser::PathNegatedPropertySetContext * /*ctx*/) override { }
  virtual void exitPathNegatedPropertySet(Sparql11Parser::PathNegatedPropertySetContext * /*ctx*/) override { }

  virtual void enterPathOneInPropertySet(Sparql11Parser::PathOneInPropertySetContext * /*ctx*/) override { }
  virtual void exitPathOneInPropertySet(Sparql11Parser::PathOneInPropertySetContext * /*ctx*/) override { }

  virtual void enterInteger(Sparql11Parser::IntegerContext * /*ctx*/) override { }
  virtual void exitInteger(Sparql11Parser::IntegerContext * /*ctx*/) override { }

  virtual void enterTriplesNode(Sparql11Parser::TriplesNodeContext * /*ctx*/) override { }
  virtual void exitTriplesNode(Sparql11Parser::TriplesNodeContext * /*ctx*/) override { }

  virtual void enterBlankNodePropertyList(Sparql11Parser::BlankNodePropertyListContext * /*ctx*/) override { }
  virtual void exitBlankNodePropertyList(Sparql11Parser::BlankNodePropertyListContext * /*ctx*/) override { }

  virtual void enterCollection(Sparql11Parser::CollectionContext * /*ctx*/) override { }
  virtual void exitCollection(Sparql11Parser::CollectionContext * /*ctx*/) override { }

  virtual void enterGraphNode(Sparql11Parser::GraphNodeContext * /*ctx*/) override { }
  virtual void exitGraphNode(Sparql11Parser::GraphNodeContext * /*ctx*/) override { }

  virtual void enterVarOrTerm(Sparql11Parser::VarOrTermContext * /*ctx*/) override { }
  virtual void exitVarOrTerm(Sparql11Parser::VarOrTermContext * /*ctx*/) override { }

  virtual void enterVarOrIriRef(Sparql11Parser::VarOrIriRefContext * /*ctx*/) override { }
  virtual void exitVarOrIriRef(Sparql11Parser::VarOrIriRefContext * /*ctx*/) override { }

  virtual void enterVariable(Sparql11Parser::VariableContext * /*ctx*/) override { }
  virtual void exitVariable(Sparql11Parser::VariableContext * /*ctx*/) override { }

  virtual void enterGraphTerm(Sparql11Parser::GraphTermContext * /*ctx*/) override { }
  virtual void exitGraphTerm(Sparql11Parser::GraphTermContext * /*ctx*/) override { }

  virtual void enterExpression(Sparql11Parser::ExpressionContext * /*ctx*/) override { }
  virtual void exitExpression(Sparql11Parser::ExpressionContext * /*ctx*/) override { }

  virtual void enterConditionalOrExpression(Sparql11Parser::ConditionalOrExpressionContext * /*ctx*/) override { }
  virtual void exitConditionalOrExpression(Sparql11Parser::ConditionalOrExpressionContext * /*ctx*/) override { }

  virtual void enterConditionalAndExpression(Sparql11Parser::ConditionalAndExpressionContext * /*ctx*/) override { }
  virtual void exitConditionalAndExpression(Sparql11Parser::ConditionalAndExpressionContext * /*ctx*/) override { }

  virtual void enterValueLogical(Sparql11Parser::ValueLogicalContext * /*ctx*/) override { }
  virtual void exitValueLogical(Sparql11Parser::ValueLogicalContext * /*ctx*/) override { }

  virtual void enterRelationalExpression(Sparql11Parser::RelationalExpressionContext * /*ctx*/) override { }
  virtual void exitRelationalExpression(Sparql11Parser::RelationalExpressionContext * /*ctx*/) override { }

  virtual void enterNumericExpression(Sparql11Parser::NumericExpressionContext * /*ctx*/) override { }
  virtual void exitNumericExpression(Sparql11Parser::NumericExpressionContext * /*ctx*/) override { }

  virtual void enterAdditiveExpression(Sparql11Parser::AdditiveExpressionContext * /*ctx*/) override { }
  virtual void exitAdditiveExpression(Sparql11Parser::AdditiveExpressionContext * /*ctx*/) override { }

  virtual void enterMultiplicativeExpression(Sparql11Parser::MultiplicativeExpressionContext * /*ctx*/) override { }
  virtual void exitMultiplicativeExpression(Sparql11Parser::MultiplicativeExpressionContext * /*ctx*/) override { }

  virtual void enterUnaryExpression(Sparql11Parser::UnaryExpressionContext * /*ctx*/) override { }
  virtual void exitUnaryExpression(Sparql11Parser::UnaryExpressionContext * /*ctx*/) override { }

  virtual void enterPrimaryExpression(Sparql11Parser::PrimaryExpressionContext * /*ctx*/) override { }
  virtual void exitPrimaryExpression(Sparql11Parser::PrimaryExpressionContext * /*ctx*/) override { }

  virtual void enterBrackettedExpression(Sparql11Parser::BrackettedExpressionContext * /*ctx*/) override { }
  virtual void exitBrackettedExpression(Sparql11Parser::BrackettedExpressionContext * /*ctx*/) override { }

  virtual void enterBuiltInCall(Sparql11Parser::BuiltInCallContext * /*ctx*/) override { }
  virtual void exitBuiltInCall(Sparql11Parser::BuiltInCallContext * /*ctx*/) override { }

  virtual void enterRegexExpression(Sparql11Parser::RegexExpressionContext * /*ctx*/) override { }
  virtual void exitRegexExpression(Sparql11Parser::RegexExpressionContext * /*ctx*/) override { }

  virtual void enterExistsFunc(Sparql11Parser::ExistsFuncContext * /*ctx*/) override { }
  virtual void exitExistsFunc(Sparql11Parser::ExistsFuncContext * /*ctx*/) override { }

  virtual void enterNotExistsFunc(Sparql11Parser::NotExistsFuncContext * /*ctx*/) override { }
  virtual void exitNotExistsFunc(Sparql11Parser::NotExistsFuncContext * /*ctx*/) override { }

  virtual void enterAggregate(Sparql11Parser::AggregateContext * /*ctx*/) override { }
  virtual void exitAggregate(Sparql11Parser::AggregateContext * /*ctx*/) override { }

  virtual void enterIriRefOrFunction(Sparql11Parser::IriRefOrFunctionContext * /*ctx*/) override { }
  virtual void exitIriRefOrFunction(Sparql11Parser::IriRefOrFunctionContext * /*ctx*/) override { }

  virtual void enterRdfLiteral(Sparql11Parser::RdfLiteralContext * /*ctx*/) override { }
  virtual void exitRdfLiteral(Sparql11Parser::RdfLiteralContext * /*ctx*/) override { }

  virtual void enterNumericLiteral(Sparql11Parser::NumericLiteralContext * /*ctx*/) override { }
  virtual void exitNumericLiteral(Sparql11Parser::NumericLiteralContext * /*ctx*/) override { }

  virtual void enterNumericLiteralUnsigned(Sparql11Parser::NumericLiteralUnsignedContext * /*ctx*/) override { }
  virtual void exitNumericLiteralUnsigned(Sparql11Parser::NumericLiteralUnsignedContext * /*ctx*/) override { }

  virtual void enterNumericLiteralPositive(Sparql11Parser::NumericLiteralPositiveContext * /*ctx*/) override { }
  virtual void exitNumericLiteralPositive(Sparql11Parser::NumericLiteralPositiveContext * /*ctx*/) override { }

  virtual void enterNumericLiteralNegative(Sparql11Parser::NumericLiteralNegativeContext * /*ctx*/) override { }
  virtual void exitNumericLiteralNegative(Sparql11Parser::NumericLiteralNegativeContext * /*ctx*/) override { }

  virtual void enterBooleanLiteral(Sparql11Parser::BooleanLiteralContext * /*ctx*/) override { }
  virtual void exitBooleanLiteral(Sparql11Parser::BooleanLiteralContext * /*ctx*/) override { }

  virtual void enterString(Sparql11Parser::StringContext * /*ctx*/) override { }
  virtual void exitString(Sparql11Parser::StringContext * /*ctx*/) override { }

  virtual void enterIriRef(Sparql11Parser::IriRefContext * /*ctx*/) override { }
  virtual void exitIriRef(Sparql11Parser::IriRefContext * /*ctx*/) override { }

  virtual void enterPrefixedName(Sparql11Parser::PrefixedNameContext * /*ctx*/) override { }
  virtual void exitPrefixedName(Sparql11Parser::PrefixedNameContext * /*ctx*/) override { }

  virtual void enterBlankNode(Sparql11Parser::BlankNodeContext * /*ctx*/) override { }
  virtual void exitBlankNode(Sparql11Parser::BlankNodeContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

