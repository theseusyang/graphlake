
// Generated from Sparql11.g4 by ANTLR 4.6

#pragma once


#include "antlr4-runtime.h"
#include "Sparql11Visitor.h"


/**
 * This class provides an empty implementation of Sparql11Visitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  Sparql11BaseVisitor : public Sparql11Visitor {
public:

  virtual antlrcpp::Any visitQueryUnit(Sparql11Parser::QueryUnitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitQuery(Sparql11Parser::QueryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPrologue(Sparql11Parser::PrologueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBaseDecl(Sparql11Parser::BaseDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPrefixDecl(Sparql11Parser::PrefixDeclContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSelectQuery(Sparql11Parser::SelectQueryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSubSelect(Sparql11Parser::SubSelectContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSelectClause(Sparql11Parser::SelectClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstructQuery(Sparql11Parser::ConstructQueryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDescribeQuery(Sparql11Parser::DescribeQueryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAskQuery(Sparql11Parser::AskQueryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDatasetClause(Sparql11Parser::DatasetClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDefaultGraphClause(Sparql11Parser::DefaultGraphClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNamedGraphClause(Sparql11Parser::NamedGraphClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSourceSelector(Sparql11Parser::SourceSelectorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitWhereClause(Sparql11Parser::WhereClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSolutionModifier(Sparql11Parser::SolutionModifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGroupClause(Sparql11Parser::GroupClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGroupCondition(Sparql11Parser::GroupConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitHavingClause(Sparql11Parser::HavingClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitHavingCondition(Sparql11Parser::HavingConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOrderClause(Sparql11Parser::OrderClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOrderCondition(Sparql11Parser::OrderConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLimitOffsetClauses(Sparql11Parser::LimitOffsetClausesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLimitClause(Sparql11Parser::LimitClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOffsetClause(Sparql11Parser::OffsetClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBindingsClause(Sparql11Parser::BindingsClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBindingValue(Sparql11Parser::BindingValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUpdateUnit(Sparql11Parser::UpdateUnitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUpdate(Sparql11Parser::UpdateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUpdate1(Sparql11Parser::Update1Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitLoad(Sparql11Parser::LoadContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitClear(Sparql11Parser::ClearContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDrop(Sparql11Parser::DropContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCreate(Sparql11Parser::CreateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInsertData(Sparql11Parser::InsertDataContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDeleteData(Sparql11Parser::DeleteDataContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDeleteWhere(Sparql11Parser::DeleteWhereContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitModify(Sparql11Parser::ModifyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitDeleteClause(Sparql11Parser::DeleteClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInsertClause(Sparql11Parser::InsertClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUsingClause(Sparql11Parser::UsingClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGraphRef(Sparql11Parser::GraphRefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGraphRefAll(Sparql11Parser::GraphRefAllContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitQuadPattern(Sparql11Parser::QuadPatternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitQuadData(Sparql11Parser::QuadDataContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitQuads(Sparql11Parser::QuadsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitQuadsNotTriples(Sparql11Parser::QuadsNotTriplesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTriplesTemplate(Sparql11Parser::TriplesTemplateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGroupGraphPattern(Sparql11Parser::GroupGraphPatternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGroupGraphPatternSub(Sparql11Parser::GroupGraphPatternSubContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTriplesBlock(Sparql11Parser::TriplesBlockContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGraphPatternNotTriples(Sparql11Parser::GraphPatternNotTriplesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitOptionalGraphPattern(Sparql11Parser::OptionalGraphPatternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGraphGraphPattern(Sparql11Parser::GraphGraphPatternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitServiceGraphPattern(Sparql11Parser::ServiceGraphPatternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMinusGraphPattern(Sparql11Parser::MinusGraphPatternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGroupOrUnionGraphPattern(Sparql11Parser::GroupOrUnionGraphPatternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFilter(Sparql11Parser::FilterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstraint(Sparql11Parser::ConstraintContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFunctionCall(Sparql11Parser::FunctionCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitArgList(Sparql11Parser::ArgListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpressionList(Sparql11Parser::ExpressionListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstructTemplate(Sparql11Parser::ConstructTemplateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConstructTriples(Sparql11Parser::ConstructTriplesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTriplesSameSubject(Sparql11Parser::TriplesSameSubjectContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPropertyListNotEmpty(Sparql11Parser::PropertyListNotEmptyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPropertyList(Sparql11Parser::PropertyListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitObjectList(Sparql11Parser::ObjectListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitObject(Sparql11Parser::ObjectContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVerb(Sparql11Parser::VerbContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTriplesSameSubjectPath(Sparql11Parser::TriplesSameSubjectPathContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPropertyListNotEmptyPath(Sparql11Parser::PropertyListNotEmptyPathContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPropertyListPath(Sparql11Parser::PropertyListPathContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVerbPath(Sparql11Parser::VerbPathContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVerbSimple(Sparql11Parser::VerbSimpleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPath(Sparql11Parser::PathContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPathAlternative(Sparql11Parser::PathAlternativeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPathSequence(Sparql11Parser::PathSequenceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPathElt(Sparql11Parser::PathEltContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPathEltOrInverse(Sparql11Parser::PathEltOrInverseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPathMod(Sparql11Parser::PathModContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPathPrimary(Sparql11Parser::PathPrimaryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPathNegatedPropertySet(Sparql11Parser::PathNegatedPropertySetContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPathOneInPropertySet(Sparql11Parser::PathOneInPropertySetContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitInteger(Sparql11Parser::IntegerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitTriplesNode(Sparql11Parser::TriplesNodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBlankNodePropertyList(Sparql11Parser::BlankNodePropertyListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCollection(Sparql11Parser::CollectionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGraphNode(Sparql11Parser::GraphNodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVarOrTerm(Sparql11Parser::VarOrTermContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVarOrIriRef(Sparql11Parser::VarOrIriRefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVariable(Sparql11Parser::VariableContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitGraphTerm(Sparql11Parser::GraphTermContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExpression(Sparql11Parser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConditionalOrExpression(Sparql11Parser::ConditionalOrExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitConditionalAndExpression(Sparql11Parser::ConditionalAndExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitValueLogical(Sparql11Parser::ValueLogicalContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRelationalExpression(Sparql11Parser::RelationalExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNumericExpression(Sparql11Parser::NumericExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAdditiveExpression(Sparql11Parser::AdditiveExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMultiplicativeExpression(Sparql11Parser::MultiplicativeExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitUnaryExpression(Sparql11Parser::UnaryExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPrimaryExpression(Sparql11Parser::PrimaryExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBrackettedExpression(Sparql11Parser::BrackettedExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBuiltInCall(Sparql11Parser::BuiltInCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRegexExpression(Sparql11Parser::RegexExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitExistsFunc(Sparql11Parser::ExistsFuncContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNotExistsFunc(Sparql11Parser::NotExistsFuncContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAggregate(Sparql11Parser::AggregateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIriRefOrFunction(Sparql11Parser::IriRefOrFunctionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRdfLiteral(Sparql11Parser::RdfLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNumericLiteral(Sparql11Parser::NumericLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNumericLiteralUnsigned(Sparql11Parser::NumericLiteralUnsignedContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNumericLiteralPositive(Sparql11Parser::NumericLiteralPositiveContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNumericLiteralNegative(Sparql11Parser::NumericLiteralNegativeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBooleanLiteral(Sparql11Parser::BooleanLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitString(Sparql11Parser::StringContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIriRef(Sparql11Parser::IriRefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitPrefixedName(Sparql11Parser::PrefixedNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitBlankNode(Sparql11Parser::BlankNodeContext *ctx) override {
    return visitChildren(ctx);
  }


};

