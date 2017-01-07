
// Generated from Sparql11.g4 by ANTLR 4.6

#pragma once


#include "antlr4-runtime.h"
#include "Sparql11Parser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by Sparql11Parser.
 */
class  Sparql11Visitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by Sparql11Parser.
   */
    virtual antlrcpp::Any visitQueryUnit(Sparql11Parser::QueryUnitContext *context) = 0;

    virtual antlrcpp::Any visitQuery(Sparql11Parser::QueryContext *context) = 0;

    virtual antlrcpp::Any visitPrologue(Sparql11Parser::PrologueContext *context) = 0;

    virtual antlrcpp::Any visitBaseDecl(Sparql11Parser::BaseDeclContext *context) = 0;

    virtual antlrcpp::Any visitPrefixDecl(Sparql11Parser::PrefixDeclContext *context) = 0;

    virtual antlrcpp::Any visitSelectQuery(Sparql11Parser::SelectQueryContext *context) = 0;

    virtual antlrcpp::Any visitSubSelect(Sparql11Parser::SubSelectContext *context) = 0;

    virtual antlrcpp::Any visitSelectClause(Sparql11Parser::SelectClauseContext *context) = 0;

    virtual antlrcpp::Any visitConstructQuery(Sparql11Parser::ConstructQueryContext *context) = 0;

    virtual antlrcpp::Any visitDescribeQuery(Sparql11Parser::DescribeQueryContext *context) = 0;

    virtual antlrcpp::Any visitAskQuery(Sparql11Parser::AskQueryContext *context) = 0;

    virtual antlrcpp::Any visitDatasetClause(Sparql11Parser::DatasetClauseContext *context) = 0;

    virtual antlrcpp::Any visitDefaultGraphClause(Sparql11Parser::DefaultGraphClauseContext *context) = 0;

    virtual antlrcpp::Any visitNamedGraphClause(Sparql11Parser::NamedGraphClauseContext *context) = 0;

    virtual antlrcpp::Any visitSourceSelector(Sparql11Parser::SourceSelectorContext *context) = 0;

    virtual antlrcpp::Any visitWhereClause(Sparql11Parser::WhereClauseContext *context) = 0;

    virtual antlrcpp::Any visitSolutionModifier(Sparql11Parser::SolutionModifierContext *context) = 0;

    virtual antlrcpp::Any visitGroupClause(Sparql11Parser::GroupClauseContext *context) = 0;

    virtual antlrcpp::Any visitGroupCondition(Sparql11Parser::GroupConditionContext *context) = 0;

    virtual antlrcpp::Any visitHavingClause(Sparql11Parser::HavingClauseContext *context) = 0;

    virtual antlrcpp::Any visitHavingCondition(Sparql11Parser::HavingConditionContext *context) = 0;

    virtual antlrcpp::Any visitOrderClause(Sparql11Parser::OrderClauseContext *context) = 0;

    virtual antlrcpp::Any visitOrderCondition(Sparql11Parser::OrderConditionContext *context) = 0;

    virtual antlrcpp::Any visitLimitOffsetClauses(Sparql11Parser::LimitOffsetClausesContext *context) = 0;

    virtual antlrcpp::Any visitLimitClause(Sparql11Parser::LimitClauseContext *context) = 0;

    virtual antlrcpp::Any visitOffsetClause(Sparql11Parser::OffsetClauseContext *context) = 0;

    virtual antlrcpp::Any visitBindingsClause(Sparql11Parser::BindingsClauseContext *context) = 0;

    virtual antlrcpp::Any visitBindingValue(Sparql11Parser::BindingValueContext *context) = 0;

    virtual antlrcpp::Any visitUpdateUnit(Sparql11Parser::UpdateUnitContext *context) = 0;

    virtual antlrcpp::Any visitUpdate(Sparql11Parser::UpdateContext *context) = 0;

    virtual antlrcpp::Any visitUpdate1(Sparql11Parser::Update1Context *context) = 0;

    virtual antlrcpp::Any visitLoad(Sparql11Parser::LoadContext *context) = 0;

    virtual antlrcpp::Any visitClear(Sparql11Parser::ClearContext *context) = 0;

    virtual antlrcpp::Any visitDrop(Sparql11Parser::DropContext *context) = 0;

    virtual antlrcpp::Any visitCreate(Sparql11Parser::CreateContext *context) = 0;

    virtual antlrcpp::Any visitInsertData(Sparql11Parser::InsertDataContext *context) = 0;

    virtual antlrcpp::Any visitDeleteData(Sparql11Parser::DeleteDataContext *context) = 0;

    virtual antlrcpp::Any visitDeleteWhere(Sparql11Parser::DeleteWhereContext *context) = 0;

    virtual antlrcpp::Any visitModify(Sparql11Parser::ModifyContext *context) = 0;

    virtual antlrcpp::Any visitDeleteClause(Sparql11Parser::DeleteClauseContext *context) = 0;

    virtual antlrcpp::Any visitInsertClause(Sparql11Parser::InsertClauseContext *context) = 0;

    virtual antlrcpp::Any visitUsingClause(Sparql11Parser::UsingClauseContext *context) = 0;

    virtual antlrcpp::Any visitGraphRef(Sparql11Parser::GraphRefContext *context) = 0;

    virtual antlrcpp::Any visitGraphRefAll(Sparql11Parser::GraphRefAllContext *context) = 0;

    virtual antlrcpp::Any visitQuadPattern(Sparql11Parser::QuadPatternContext *context) = 0;

    virtual antlrcpp::Any visitQuadData(Sparql11Parser::QuadDataContext *context) = 0;

    virtual antlrcpp::Any visitQuads(Sparql11Parser::QuadsContext *context) = 0;

    virtual antlrcpp::Any visitQuadsNotTriples(Sparql11Parser::QuadsNotTriplesContext *context) = 0;

    virtual antlrcpp::Any visitTriplesTemplate(Sparql11Parser::TriplesTemplateContext *context) = 0;

    virtual antlrcpp::Any visitGroupGraphPattern(Sparql11Parser::GroupGraphPatternContext *context) = 0;

    virtual antlrcpp::Any visitGroupGraphPatternSub(Sparql11Parser::GroupGraphPatternSubContext *context) = 0;

    virtual antlrcpp::Any visitTriplesBlock(Sparql11Parser::TriplesBlockContext *context) = 0;

    virtual antlrcpp::Any visitGraphPatternNotTriples(Sparql11Parser::GraphPatternNotTriplesContext *context) = 0;

    virtual antlrcpp::Any visitOptionalGraphPattern(Sparql11Parser::OptionalGraphPatternContext *context) = 0;

    virtual antlrcpp::Any visitGraphGraphPattern(Sparql11Parser::GraphGraphPatternContext *context) = 0;

    virtual antlrcpp::Any visitServiceGraphPattern(Sparql11Parser::ServiceGraphPatternContext *context) = 0;

    virtual antlrcpp::Any visitMinusGraphPattern(Sparql11Parser::MinusGraphPatternContext *context) = 0;

    virtual antlrcpp::Any visitGroupOrUnionGraphPattern(Sparql11Parser::GroupOrUnionGraphPatternContext *context) = 0;

    virtual antlrcpp::Any visitFilter(Sparql11Parser::FilterContext *context) = 0;

    virtual antlrcpp::Any visitConstraint(Sparql11Parser::ConstraintContext *context) = 0;

    virtual antlrcpp::Any visitFunctionCall(Sparql11Parser::FunctionCallContext *context) = 0;

    virtual antlrcpp::Any visitArgList(Sparql11Parser::ArgListContext *context) = 0;

    virtual antlrcpp::Any visitExpressionList(Sparql11Parser::ExpressionListContext *context) = 0;

    virtual antlrcpp::Any visitConstructTemplate(Sparql11Parser::ConstructTemplateContext *context) = 0;

    virtual antlrcpp::Any visitConstructTriples(Sparql11Parser::ConstructTriplesContext *context) = 0;

    virtual antlrcpp::Any visitTriplesSameSubject(Sparql11Parser::TriplesSameSubjectContext *context) = 0;

    virtual antlrcpp::Any visitPropertyListNotEmpty(Sparql11Parser::PropertyListNotEmptyContext *context) = 0;

    virtual antlrcpp::Any visitPropertyList(Sparql11Parser::PropertyListContext *context) = 0;

    virtual antlrcpp::Any visitObjectList(Sparql11Parser::ObjectListContext *context) = 0;

    virtual antlrcpp::Any visitObject(Sparql11Parser::ObjectContext *context) = 0;

    virtual antlrcpp::Any visitVerb(Sparql11Parser::VerbContext *context) = 0;

    virtual antlrcpp::Any visitTriplesSameSubjectPath(Sparql11Parser::TriplesSameSubjectPathContext *context) = 0;

    virtual antlrcpp::Any visitPropertyListNotEmptyPath(Sparql11Parser::PropertyListNotEmptyPathContext *context) = 0;

    virtual antlrcpp::Any visitPropertyListPath(Sparql11Parser::PropertyListPathContext *context) = 0;

    virtual antlrcpp::Any visitVerbPath(Sparql11Parser::VerbPathContext *context) = 0;

    virtual antlrcpp::Any visitVerbSimple(Sparql11Parser::VerbSimpleContext *context) = 0;

    virtual antlrcpp::Any visitPath(Sparql11Parser::PathContext *context) = 0;

    virtual antlrcpp::Any visitPathAlternative(Sparql11Parser::PathAlternativeContext *context) = 0;

    virtual antlrcpp::Any visitPathSequence(Sparql11Parser::PathSequenceContext *context) = 0;

    virtual antlrcpp::Any visitPathElt(Sparql11Parser::PathEltContext *context) = 0;

    virtual antlrcpp::Any visitPathEltOrInverse(Sparql11Parser::PathEltOrInverseContext *context) = 0;

    virtual antlrcpp::Any visitPathMod(Sparql11Parser::PathModContext *context) = 0;

    virtual antlrcpp::Any visitPathPrimary(Sparql11Parser::PathPrimaryContext *context) = 0;

    virtual antlrcpp::Any visitPathNegatedPropertySet(Sparql11Parser::PathNegatedPropertySetContext *context) = 0;

    virtual antlrcpp::Any visitPathOneInPropertySet(Sparql11Parser::PathOneInPropertySetContext *context) = 0;

    virtual antlrcpp::Any visitInteger(Sparql11Parser::IntegerContext *context) = 0;

    virtual antlrcpp::Any visitTriplesNode(Sparql11Parser::TriplesNodeContext *context) = 0;

    virtual antlrcpp::Any visitBlankNodePropertyList(Sparql11Parser::BlankNodePropertyListContext *context) = 0;

    virtual antlrcpp::Any visitCollection(Sparql11Parser::CollectionContext *context) = 0;

    virtual antlrcpp::Any visitGraphNode(Sparql11Parser::GraphNodeContext *context) = 0;

    virtual antlrcpp::Any visitVarOrTerm(Sparql11Parser::VarOrTermContext *context) = 0;

    virtual antlrcpp::Any visitVarOrIriRef(Sparql11Parser::VarOrIriRefContext *context) = 0;

    virtual antlrcpp::Any visitVariable(Sparql11Parser::VariableContext *context) = 0;

    virtual antlrcpp::Any visitGraphTerm(Sparql11Parser::GraphTermContext *context) = 0;

    virtual antlrcpp::Any visitExpression(Sparql11Parser::ExpressionContext *context) = 0;

    virtual antlrcpp::Any visitConditionalOrExpression(Sparql11Parser::ConditionalOrExpressionContext *context) = 0;

    virtual antlrcpp::Any visitConditionalAndExpression(Sparql11Parser::ConditionalAndExpressionContext *context) = 0;

    virtual antlrcpp::Any visitValueLogical(Sparql11Parser::ValueLogicalContext *context) = 0;

    virtual antlrcpp::Any visitRelationalExpression(Sparql11Parser::RelationalExpressionContext *context) = 0;

    virtual antlrcpp::Any visitNumericExpression(Sparql11Parser::NumericExpressionContext *context) = 0;

    virtual antlrcpp::Any visitAdditiveExpression(Sparql11Parser::AdditiveExpressionContext *context) = 0;

    virtual antlrcpp::Any visitMultiplicativeExpression(Sparql11Parser::MultiplicativeExpressionContext *context) = 0;

    virtual antlrcpp::Any visitUnaryExpression(Sparql11Parser::UnaryExpressionContext *context) = 0;

    virtual antlrcpp::Any visitPrimaryExpression(Sparql11Parser::PrimaryExpressionContext *context) = 0;

    virtual antlrcpp::Any visitBrackettedExpression(Sparql11Parser::BrackettedExpressionContext *context) = 0;

    virtual antlrcpp::Any visitBuiltInCall(Sparql11Parser::BuiltInCallContext *context) = 0;

    virtual antlrcpp::Any visitRegexExpression(Sparql11Parser::RegexExpressionContext *context) = 0;

    virtual antlrcpp::Any visitExistsFunc(Sparql11Parser::ExistsFuncContext *context) = 0;

    virtual antlrcpp::Any visitNotExistsFunc(Sparql11Parser::NotExistsFuncContext *context) = 0;

    virtual antlrcpp::Any visitAggregate(Sparql11Parser::AggregateContext *context) = 0;

    virtual antlrcpp::Any visitIriRefOrFunction(Sparql11Parser::IriRefOrFunctionContext *context) = 0;

    virtual antlrcpp::Any visitRdfLiteral(Sparql11Parser::RdfLiteralContext *context) = 0;

    virtual antlrcpp::Any visitNumericLiteral(Sparql11Parser::NumericLiteralContext *context) = 0;

    virtual antlrcpp::Any visitNumericLiteralUnsigned(Sparql11Parser::NumericLiteralUnsignedContext *context) = 0;

    virtual antlrcpp::Any visitNumericLiteralPositive(Sparql11Parser::NumericLiteralPositiveContext *context) = 0;

    virtual antlrcpp::Any visitNumericLiteralNegative(Sparql11Parser::NumericLiteralNegativeContext *context) = 0;

    virtual antlrcpp::Any visitBooleanLiteral(Sparql11Parser::BooleanLiteralContext *context) = 0;

    virtual antlrcpp::Any visitString(Sparql11Parser::StringContext *context) = 0;

    virtual antlrcpp::Any visitIriRef(Sparql11Parser::IriRefContext *context) = 0;

    virtual antlrcpp::Any visitPrefixedName(Sparql11Parser::PrefixedNameContext *context) = 0;

    virtual antlrcpp::Any visitBlankNode(Sparql11Parser::BlankNodeContext *context) = 0;


};

