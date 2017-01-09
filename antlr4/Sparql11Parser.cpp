
// Generated from Sparql11.g4 by ANTLR 4.6


#include "Sparql11Visitor.h"

#include "Sparql11Parser.h"


using namespace antlrcpp;
using namespace antlr4;

Sparql11Parser::Sparql11Parser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

Sparql11Parser::~Sparql11Parser() {
  delete _interpreter;
}

std::string Sparql11Parser::getGrammarFileName() const {
  return "Sparql11.g4";
}

const std::vector<std::string>& Sparql11Parser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& Sparql11Parser::getVocabulary() const {
  return _vocabulary;
}


//----------------- QueryUnitContext ------------------------------------------------------------------

Sparql11Parser::QueryUnitContext::QueryUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::QueryContext* Sparql11Parser::QueryUnitContext::query() {
  return getRuleContext<Sparql11Parser::QueryContext>(0);
}


size_t Sparql11Parser::QueryUnitContext::getRuleIndex() const {
  return Sparql11Parser::RuleQueryUnit;
}

antlrcpp::Any Sparql11Parser::QueryUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitQueryUnit(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::QueryUnitContext* Sparql11Parser::queryUnit() {
  QueryUnitContext *_localctx = _tracker.createInstance<QueryUnitContext>(_ctx, getState());
  enterRule(_localctx, 0, Sparql11Parser::RuleQueryUnit);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(242);
    query();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QueryContext ------------------------------------------------------------------

Sparql11Parser::QueryContext::QueryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::PrologueContext* Sparql11Parser::QueryContext::prologue() {
  return getRuleContext<Sparql11Parser::PrologueContext>(0);
}

Sparql11Parser::SelectQueryContext* Sparql11Parser::QueryContext::selectQuery() {
  return getRuleContext<Sparql11Parser::SelectQueryContext>(0);
}

Sparql11Parser::ConstructQueryContext* Sparql11Parser::QueryContext::constructQuery() {
  return getRuleContext<Sparql11Parser::ConstructQueryContext>(0);
}

Sparql11Parser::DescribeQueryContext* Sparql11Parser::QueryContext::describeQuery() {
  return getRuleContext<Sparql11Parser::DescribeQueryContext>(0);
}

Sparql11Parser::AskQueryContext* Sparql11Parser::QueryContext::askQuery() {
  return getRuleContext<Sparql11Parser::AskQueryContext>(0);
}


size_t Sparql11Parser::QueryContext::getRuleIndex() const {
  return Sparql11Parser::RuleQuery;
}

antlrcpp::Any Sparql11Parser::QueryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitQuery(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::QueryContext* Sparql11Parser::query() {
  QueryContext *_localctx = _tracker.createInstance<QueryContext>(_ctx, getState());
  enterRule(_localctx, 2, Sparql11Parser::RuleQuery);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(244);
    prologue();
    setState(249);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::SELECT: {
        setState(245);
        selectQuery();
        break;
      }

      case Sparql11Parser::CONSTRUCT: {
        setState(246);
        constructQuery();
        break;
      }

      case Sparql11Parser::DESCRIBE: {
        setState(247);
        describeQuery();
        break;
      }

      case Sparql11Parser::ASK: {
        setState(248);
        askQuery();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrologueContext ------------------------------------------------------------------

Sparql11Parser::PrologueContext::PrologueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::BaseDeclContext* Sparql11Parser::PrologueContext::baseDecl() {
  return getRuleContext<Sparql11Parser::BaseDeclContext>(0);
}

std::vector<Sparql11Parser::PrefixDeclContext *> Sparql11Parser::PrologueContext::prefixDecl() {
  return getRuleContexts<Sparql11Parser::PrefixDeclContext>();
}

Sparql11Parser::PrefixDeclContext* Sparql11Parser::PrologueContext::prefixDecl(size_t i) {
  return getRuleContext<Sparql11Parser::PrefixDeclContext>(i);
}


size_t Sparql11Parser::PrologueContext::getRuleIndex() const {
  return Sparql11Parser::RulePrologue;
}

antlrcpp::Any Sparql11Parser::PrologueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitPrologue(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::PrologueContext* Sparql11Parser::prologue() {
  PrologueContext *_localctx = _tracker.createInstance<PrologueContext>(_ctx, getState());
  enterRule(_localctx, 4, Sparql11Parser::RulePrologue);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(252);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Sparql11Parser::BASE) {
      setState(251);
      baseDecl();
    }
    setState(257);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Sparql11Parser::PREFIX) {
      setState(254);
      prefixDecl();
      setState(259);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BaseDeclContext ------------------------------------------------------------------

Sparql11Parser::BaseDeclContext::BaseDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::BaseDeclContext::BASE() {
  return getToken(Sparql11Parser::BASE, 0);
}

tree::TerminalNode* Sparql11Parser::BaseDeclContext::IRI_REF() {
  return getToken(Sparql11Parser::IRI_REF, 0);
}


size_t Sparql11Parser::BaseDeclContext::getRuleIndex() const {
  return Sparql11Parser::RuleBaseDecl;
}

antlrcpp::Any Sparql11Parser::BaseDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitBaseDecl(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::BaseDeclContext* Sparql11Parser::baseDecl() {
  BaseDeclContext *_localctx = _tracker.createInstance<BaseDeclContext>(_ctx, getState());
  enterRule(_localctx, 6, Sparql11Parser::RuleBaseDecl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(260);
    match(Sparql11Parser::BASE);
    setState(261);
    match(Sparql11Parser::IRI_REF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrefixDeclContext ------------------------------------------------------------------

Sparql11Parser::PrefixDeclContext::PrefixDeclContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::PrefixDeclContext::PREFIX() {
  return getToken(Sparql11Parser::PREFIX, 0);
}

tree::TerminalNode* Sparql11Parser::PrefixDeclContext::PNAME_NS() {
  return getToken(Sparql11Parser::PNAME_NS, 0);
}

tree::TerminalNode* Sparql11Parser::PrefixDeclContext::IRI_REF() {
  return getToken(Sparql11Parser::IRI_REF, 0);
}


size_t Sparql11Parser::PrefixDeclContext::getRuleIndex() const {
  return Sparql11Parser::RulePrefixDecl;
}

antlrcpp::Any Sparql11Parser::PrefixDeclContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitPrefixDecl(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::PrefixDeclContext* Sparql11Parser::prefixDecl() {
  PrefixDeclContext *_localctx = _tracker.createInstance<PrefixDeclContext>(_ctx, getState());
  enterRule(_localctx, 8, Sparql11Parser::RulePrefixDecl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(263);
    match(Sparql11Parser::PREFIX);
    setState(264);
    match(Sparql11Parser::PNAME_NS);
    setState(265);
    match(Sparql11Parser::IRI_REF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectQueryContext ------------------------------------------------------------------

Sparql11Parser::SelectQueryContext::SelectQueryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::SelectClauseContext* Sparql11Parser::SelectQueryContext::selectClause() {
  return getRuleContext<Sparql11Parser::SelectClauseContext>(0);
}

Sparql11Parser::WhereClauseContext* Sparql11Parser::SelectQueryContext::whereClause() {
  return getRuleContext<Sparql11Parser::WhereClauseContext>(0);
}

Sparql11Parser::SolutionModifierContext* Sparql11Parser::SelectQueryContext::solutionModifier() {
  return getRuleContext<Sparql11Parser::SolutionModifierContext>(0);
}

Sparql11Parser::BindingsClauseContext* Sparql11Parser::SelectQueryContext::bindingsClause() {
  return getRuleContext<Sparql11Parser::BindingsClauseContext>(0);
}

std::vector<Sparql11Parser::DatasetClauseContext *> Sparql11Parser::SelectQueryContext::datasetClause() {
  return getRuleContexts<Sparql11Parser::DatasetClauseContext>();
}

Sparql11Parser::DatasetClauseContext* Sparql11Parser::SelectQueryContext::datasetClause(size_t i) {
  return getRuleContext<Sparql11Parser::DatasetClauseContext>(i);
}


size_t Sparql11Parser::SelectQueryContext::getRuleIndex() const {
  return Sparql11Parser::RuleSelectQuery;
}

antlrcpp::Any Sparql11Parser::SelectQueryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitSelectQuery(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::SelectQueryContext* Sparql11Parser::selectQuery() {
  SelectQueryContext *_localctx = _tracker.createInstance<SelectQueryContext>(_ctx, getState());
  enterRule(_localctx, 10, Sparql11Parser::RuleSelectQuery);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(267);
    selectClause();
    setState(271);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Sparql11Parser::FROM) {
      setState(268);
      datasetClause();
      setState(273);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(274);
    whereClause();
    setState(275);
    solutionModifier();
    setState(276);
    bindingsClause();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SubSelectContext ------------------------------------------------------------------

Sparql11Parser::SubSelectContext::SubSelectContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::SelectClauseContext* Sparql11Parser::SubSelectContext::selectClause() {
  return getRuleContext<Sparql11Parser::SelectClauseContext>(0);
}

Sparql11Parser::WhereClauseContext* Sparql11Parser::SubSelectContext::whereClause() {
  return getRuleContext<Sparql11Parser::WhereClauseContext>(0);
}

Sparql11Parser::SolutionModifierContext* Sparql11Parser::SubSelectContext::solutionModifier() {
  return getRuleContext<Sparql11Parser::SolutionModifierContext>(0);
}


size_t Sparql11Parser::SubSelectContext::getRuleIndex() const {
  return Sparql11Parser::RuleSubSelect;
}

antlrcpp::Any Sparql11Parser::SubSelectContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitSubSelect(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::SubSelectContext* Sparql11Parser::subSelect() {
  SubSelectContext *_localctx = _tracker.createInstance<SubSelectContext>(_ctx, getState());
  enterRule(_localctx, 12, Sparql11Parser::RuleSubSelect);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(278);
    selectClause();
    setState(279);
    whereClause();
    setState(280);
    solutionModifier();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectClauseContext ------------------------------------------------------------------

Sparql11Parser::SelectClauseContext::SelectClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::SelectClauseContext::SELECT() {
  return getToken(Sparql11Parser::SELECT, 0);
}

tree::TerminalNode* Sparql11Parser::SelectClauseContext::ASTERISK() {
  return getToken(Sparql11Parser::ASTERISK, 0);
}

tree::TerminalNode* Sparql11Parser::SelectClauseContext::DISTINCT() {
  return getToken(Sparql11Parser::DISTINCT, 0);
}

tree::TerminalNode* Sparql11Parser::SelectClauseContext::REDUCED() {
  return getToken(Sparql11Parser::REDUCED, 0);
}

std::vector<Sparql11Parser::VariableContext *> Sparql11Parser::SelectClauseContext::variable() {
  return getRuleContexts<Sparql11Parser::VariableContext>();
}

Sparql11Parser::VariableContext* Sparql11Parser::SelectClauseContext::variable(size_t i) {
  return getRuleContext<Sparql11Parser::VariableContext>(i);
}

std::vector<tree::TerminalNode *> Sparql11Parser::SelectClauseContext::OPEN_BRACE() {
  return getTokens(Sparql11Parser::OPEN_BRACE);
}

tree::TerminalNode* Sparql11Parser::SelectClauseContext::OPEN_BRACE(size_t i) {
  return getToken(Sparql11Parser::OPEN_BRACE, i);
}

std::vector<Sparql11Parser::ExpressionContext *> Sparql11Parser::SelectClauseContext::expression() {
  return getRuleContexts<Sparql11Parser::ExpressionContext>();
}

Sparql11Parser::ExpressionContext* Sparql11Parser::SelectClauseContext::expression(size_t i) {
  return getRuleContext<Sparql11Parser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> Sparql11Parser::SelectClauseContext::AS() {
  return getTokens(Sparql11Parser::AS);
}

tree::TerminalNode* Sparql11Parser::SelectClauseContext::AS(size_t i) {
  return getToken(Sparql11Parser::AS, i);
}

std::vector<tree::TerminalNode *> Sparql11Parser::SelectClauseContext::CLOSE_BRACE() {
  return getTokens(Sparql11Parser::CLOSE_BRACE);
}

tree::TerminalNode* Sparql11Parser::SelectClauseContext::CLOSE_BRACE(size_t i) {
  return getToken(Sparql11Parser::CLOSE_BRACE, i);
}


size_t Sparql11Parser::SelectClauseContext::getRuleIndex() const {
  return Sparql11Parser::RuleSelectClause;
}

antlrcpp::Any Sparql11Parser::SelectClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitSelectClause(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::SelectClauseContext* Sparql11Parser::selectClause() {
  SelectClauseContext *_localctx = _tracker.createInstance<SelectClauseContext>(_ctx, getState());
  enterRule(_localctx, 14, Sparql11Parser::RuleSelectClause);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(282);
    match(Sparql11Parser::SELECT);
    setState(284);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Sparql11Parser::DISTINCT

    || _la == Sparql11Parser::REDUCED) {
      setState(283);
      _la = _input->LA(1);
      if (!(_la == Sparql11Parser::DISTINCT

      || _la == Sparql11Parser::REDUCED)) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
    setState(298);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::VAR1:
      case Sparql11Parser::VAR2:
      case Sparql11Parser::OPEN_BRACE: {
        setState(293); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(293);
          _errHandler->sync(this);
          switch (_input->LA(1)) {
            case Sparql11Parser::VAR1:
            case Sparql11Parser::VAR2: {
              setState(286);
              variable();
              break;
            }

            case Sparql11Parser::OPEN_BRACE: {
              setState(287);
              match(Sparql11Parser::OPEN_BRACE);
              setState(288);
              expression();
              setState(289);
              match(Sparql11Parser::AS);
              setState(290);
              variable();
              setState(291);
              match(Sparql11Parser::CLOSE_BRACE);
              break;
            }

          default:
            throw NoViableAltException(this);
          }
          setState(295); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (((((_la - 80) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 80)) & ((1ULL << (Sparql11Parser::VAR1 - 80))
          | (1ULL << (Sparql11Parser::VAR2 - 80))
          | (1ULL << (Sparql11Parser::OPEN_BRACE - 80)))) != 0));
        break;
      }

      case Sparql11Parser::ASTERISK: {
        setState(297);
        match(Sparql11Parser::ASTERISK);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstructQueryContext ------------------------------------------------------------------

Sparql11Parser::ConstructQueryContext::ConstructQueryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::ConstructQueryContext::CONSTRUCT() {
  return getToken(Sparql11Parser::CONSTRUCT, 0);
}

Sparql11Parser::ConstructTemplateContext* Sparql11Parser::ConstructQueryContext::constructTemplate() {
  return getRuleContext<Sparql11Parser::ConstructTemplateContext>(0);
}

Sparql11Parser::WhereClauseContext* Sparql11Parser::ConstructQueryContext::whereClause() {
  return getRuleContext<Sparql11Parser::WhereClauseContext>(0);
}

Sparql11Parser::SolutionModifierContext* Sparql11Parser::ConstructQueryContext::solutionModifier() {
  return getRuleContext<Sparql11Parser::SolutionModifierContext>(0);
}

std::vector<Sparql11Parser::DatasetClauseContext *> Sparql11Parser::ConstructQueryContext::datasetClause() {
  return getRuleContexts<Sparql11Parser::DatasetClauseContext>();
}

Sparql11Parser::DatasetClauseContext* Sparql11Parser::ConstructQueryContext::datasetClause(size_t i) {
  return getRuleContext<Sparql11Parser::DatasetClauseContext>(i);
}


size_t Sparql11Parser::ConstructQueryContext::getRuleIndex() const {
  return Sparql11Parser::RuleConstructQuery;
}

antlrcpp::Any Sparql11Parser::ConstructQueryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitConstructQuery(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::ConstructQueryContext* Sparql11Parser::constructQuery() {
  ConstructQueryContext *_localctx = _tracker.createInstance<ConstructQueryContext>(_ctx, getState());
  enterRule(_localctx, 16, Sparql11Parser::RuleConstructQuery);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(300);
    match(Sparql11Parser::CONSTRUCT);
    setState(301);
    constructTemplate();
    setState(305);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Sparql11Parser::FROM) {
      setState(302);
      datasetClause();
      setState(307);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(308);
    whereClause();
    setState(309);
    solutionModifier();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DescribeQueryContext ------------------------------------------------------------------

Sparql11Parser::DescribeQueryContext::DescribeQueryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::DescribeQueryContext::DESCRIBE() {
  return getToken(Sparql11Parser::DESCRIBE, 0);
}

Sparql11Parser::SolutionModifierContext* Sparql11Parser::DescribeQueryContext::solutionModifier() {
  return getRuleContext<Sparql11Parser::SolutionModifierContext>(0);
}

tree::TerminalNode* Sparql11Parser::DescribeQueryContext::ASTERISK() {
  return getToken(Sparql11Parser::ASTERISK, 0);
}

std::vector<Sparql11Parser::DatasetClauseContext *> Sparql11Parser::DescribeQueryContext::datasetClause() {
  return getRuleContexts<Sparql11Parser::DatasetClauseContext>();
}

Sparql11Parser::DatasetClauseContext* Sparql11Parser::DescribeQueryContext::datasetClause(size_t i) {
  return getRuleContext<Sparql11Parser::DatasetClauseContext>(i);
}

Sparql11Parser::WhereClauseContext* Sparql11Parser::DescribeQueryContext::whereClause() {
  return getRuleContext<Sparql11Parser::WhereClauseContext>(0);
}

std::vector<Sparql11Parser::VarOrIriRefContext *> Sparql11Parser::DescribeQueryContext::varOrIriRef() {
  return getRuleContexts<Sparql11Parser::VarOrIriRefContext>();
}

Sparql11Parser::VarOrIriRefContext* Sparql11Parser::DescribeQueryContext::varOrIriRef(size_t i) {
  return getRuleContext<Sparql11Parser::VarOrIriRefContext>(i);
}


size_t Sparql11Parser::DescribeQueryContext::getRuleIndex() const {
  return Sparql11Parser::RuleDescribeQuery;
}

antlrcpp::Any Sparql11Parser::DescribeQueryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitDescribeQuery(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::DescribeQueryContext* Sparql11Parser::describeQuery() {
  DescribeQueryContext *_localctx = _tracker.createInstance<DescribeQueryContext>(_ctx, getState());
  enterRule(_localctx, 18, Sparql11Parser::RuleDescribeQuery);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(311);
    match(Sparql11Parser::DESCRIBE);
    setState(318);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::IRI_REF:
      case Sparql11Parser::PNAME_NS:
      case Sparql11Parser::PNAME_LN:
      case Sparql11Parser::VAR1:
      case Sparql11Parser::VAR2: {
        setState(313); 
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(312);
          varOrIriRef();
          setState(315); 
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (((((_la - 77) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 77)) & ((1ULL << (Sparql11Parser::IRI_REF - 77))
          | (1ULL << (Sparql11Parser::PNAME_NS - 77))
          | (1ULL << (Sparql11Parser::PNAME_LN - 77))
          | (1ULL << (Sparql11Parser::VAR1 - 77))
          | (1ULL << (Sparql11Parser::VAR2 - 77)))) != 0));
        break;
      }

      case Sparql11Parser::ASTERISK: {
        setState(317);
        match(Sparql11Parser::ASTERISK);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(323);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Sparql11Parser::FROM) {
      setState(320);
      datasetClause();
      setState(325);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(327);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Sparql11Parser::WHERE

    || _la == Sparql11Parser::OPEN_CURLY_BRACE) {
      setState(326);
      whereClause();
    }
    setState(329);
    solutionModifier();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AskQueryContext ------------------------------------------------------------------

Sparql11Parser::AskQueryContext::AskQueryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::AskQueryContext::ASK() {
  return getToken(Sparql11Parser::ASK, 0);
}

Sparql11Parser::WhereClauseContext* Sparql11Parser::AskQueryContext::whereClause() {
  return getRuleContext<Sparql11Parser::WhereClauseContext>(0);
}

std::vector<Sparql11Parser::DatasetClauseContext *> Sparql11Parser::AskQueryContext::datasetClause() {
  return getRuleContexts<Sparql11Parser::DatasetClauseContext>();
}

Sparql11Parser::DatasetClauseContext* Sparql11Parser::AskQueryContext::datasetClause(size_t i) {
  return getRuleContext<Sparql11Parser::DatasetClauseContext>(i);
}


size_t Sparql11Parser::AskQueryContext::getRuleIndex() const {
  return Sparql11Parser::RuleAskQuery;
}

antlrcpp::Any Sparql11Parser::AskQueryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitAskQuery(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::AskQueryContext* Sparql11Parser::askQuery() {
  AskQueryContext *_localctx = _tracker.createInstance<AskQueryContext>(_ctx, getState());
  enterRule(_localctx, 20, Sparql11Parser::RuleAskQuery);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(331);
    match(Sparql11Parser::ASK);
    setState(335);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Sparql11Parser::FROM) {
      setState(332);
      datasetClause();
      setState(337);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(338);
    whereClause();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DatasetClauseContext ------------------------------------------------------------------

Sparql11Parser::DatasetClauseContext::DatasetClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::DatasetClauseContext::FROM() {
  return getToken(Sparql11Parser::FROM, 0);
}

Sparql11Parser::DefaultGraphClauseContext* Sparql11Parser::DatasetClauseContext::defaultGraphClause() {
  return getRuleContext<Sparql11Parser::DefaultGraphClauseContext>(0);
}

Sparql11Parser::NamedGraphClauseContext* Sparql11Parser::DatasetClauseContext::namedGraphClause() {
  return getRuleContext<Sparql11Parser::NamedGraphClauseContext>(0);
}


size_t Sparql11Parser::DatasetClauseContext::getRuleIndex() const {
  return Sparql11Parser::RuleDatasetClause;
}

antlrcpp::Any Sparql11Parser::DatasetClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitDatasetClause(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::DatasetClauseContext* Sparql11Parser::datasetClause() {
  DatasetClauseContext *_localctx = _tracker.createInstance<DatasetClauseContext>(_ctx, getState());
  enterRule(_localctx, 22, Sparql11Parser::RuleDatasetClause);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(340);
    match(Sparql11Parser::FROM);
    setState(343);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::IRI_REF:
      case Sparql11Parser::PNAME_NS:
      case Sparql11Parser::PNAME_LN: {
        setState(341);
        defaultGraphClause();
        break;
      }

      case Sparql11Parser::NAMED: {
        setState(342);
        namedGraphClause();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DefaultGraphClauseContext ------------------------------------------------------------------

Sparql11Parser::DefaultGraphClauseContext::DefaultGraphClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::SourceSelectorContext* Sparql11Parser::DefaultGraphClauseContext::sourceSelector() {
  return getRuleContext<Sparql11Parser::SourceSelectorContext>(0);
}


size_t Sparql11Parser::DefaultGraphClauseContext::getRuleIndex() const {
  return Sparql11Parser::RuleDefaultGraphClause;
}

antlrcpp::Any Sparql11Parser::DefaultGraphClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitDefaultGraphClause(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::DefaultGraphClauseContext* Sparql11Parser::defaultGraphClause() {
  DefaultGraphClauseContext *_localctx = _tracker.createInstance<DefaultGraphClauseContext>(_ctx, getState());
  enterRule(_localctx, 24, Sparql11Parser::RuleDefaultGraphClause);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(345);
    sourceSelector();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NamedGraphClauseContext ------------------------------------------------------------------

Sparql11Parser::NamedGraphClauseContext::NamedGraphClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::NamedGraphClauseContext::NAMED() {
  return getToken(Sparql11Parser::NAMED, 0);
}

Sparql11Parser::SourceSelectorContext* Sparql11Parser::NamedGraphClauseContext::sourceSelector() {
  return getRuleContext<Sparql11Parser::SourceSelectorContext>(0);
}


size_t Sparql11Parser::NamedGraphClauseContext::getRuleIndex() const {
  return Sparql11Parser::RuleNamedGraphClause;
}

antlrcpp::Any Sparql11Parser::NamedGraphClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitNamedGraphClause(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::NamedGraphClauseContext* Sparql11Parser::namedGraphClause() {
  NamedGraphClauseContext *_localctx = _tracker.createInstance<NamedGraphClauseContext>(_ctx, getState());
  enterRule(_localctx, 26, Sparql11Parser::RuleNamedGraphClause);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(347);
    match(Sparql11Parser::NAMED);
    setState(348);
    sourceSelector();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SourceSelectorContext ------------------------------------------------------------------

Sparql11Parser::SourceSelectorContext::SourceSelectorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::IriRefContext* Sparql11Parser::SourceSelectorContext::iriRef() {
  return getRuleContext<Sparql11Parser::IriRefContext>(0);
}


size_t Sparql11Parser::SourceSelectorContext::getRuleIndex() const {
  return Sparql11Parser::RuleSourceSelector;
}

antlrcpp::Any Sparql11Parser::SourceSelectorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitSourceSelector(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::SourceSelectorContext* Sparql11Parser::sourceSelector() {
  SourceSelectorContext *_localctx = _tracker.createInstance<SourceSelectorContext>(_ctx, getState());
  enterRule(_localctx, 28, Sparql11Parser::RuleSourceSelector);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(350);
    iriRef();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WhereClauseContext ------------------------------------------------------------------

Sparql11Parser::WhereClauseContext::WhereClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::GroupGraphPatternContext* Sparql11Parser::WhereClauseContext::groupGraphPattern() {
  return getRuleContext<Sparql11Parser::GroupGraphPatternContext>(0);
}

tree::TerminalNode* Sparql11Parser::WhereClauseContext::WHERE() {
  return getToken(Sparql11Parser::WHERE, 0);
}


size_t Sparql11Parser::WhereClauseContext::getRuleIndex() const {
  return Sparql11Parser::RuleWhereClause;
}

antlrcpp::Any Sparql11Parser::WhereClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitWhereClause(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::WhereClauseContext* Sparql11Parser::whereClause() {
  WhereClauseContext *_localctx = _tracker.createInstance<WhereClauseContext>(_ctx, getState());
  enterRule(_localctx, 30, Sparql11Parser::RuleWhereClause);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(353);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Sparql11Parser::WHERE) {
      setState(352);
      match(Sparql11Parser::WHERE);
    }
    setState(355);
    groupGraphPattern();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SolutionModifierContext ------------------------------------------------------------------

Sparql11Parser::SolutionModifierContext::SolutionModifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::GroupClauseContext* Sparql11Parser::SolutionModifierContext::groupClause() {
  return getRuleContext<Sparql11Parser::GroupClauseContext>(0);
}

Sparql11Parser::HavingClauseContext* Sparql11Parser::SolutionModifierContext::havingClause() {
  return getRuleContext<Sparql11Parser::HavingClauseContext>(0);
}

Sparql11Parser::OrderClauseContext* Sparql11Parser::SolutionModifierContext::orderClause() {
  return getRuleContext<Sparql11Parser::OrderClauseContext>(0);
}

Sparql11Parser::LimitOffsetClausesContext* Sparql11Parser::SolutionModifierContext::limitOffsetClauses() {
  return getRuleContext<Sparql11Parser::LimitOffsetClausesContext>(0);
}


size_t Sparql11Parser::SolutionModifierContext::getRuleIndex() const {
  return Sparql11Parser::RuleSolutionModifier;
}

antlrcpp::Any Sparql11Parser::SolutionModifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitSolutionModifier(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::SolutionModifierContext* Sparql11Parser::solutionModifier() {
  SolutionModifierContext *_localctx = _tracker.createInstance<SolutionModifierContext>(_ctx, getState());
  enterRule(_localctx, 32, Sparql11Parser::RuleSolutionModifier);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(358);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Sparql11Parser::GROUP) {
      setState(357);
      groupClause();
    }
    setState(361);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Sparql11Parser::HAVING) {
      setState(360);
      havingClause();
    }
    setState(364);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Sparql11Parser::ORDER) {
      setState(363);
      orderClause();
    }
    setState(367);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Sparql11Parser::LIMIT

    || _la == Sparql11Parser::OFFSET) {
      setState(366);
      limitOffsetClauses();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GroupClauseContext ------------------------------------------------------------------

Sparql11Parser::GroupClauseContext::GroupClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::GroupClauseContext::GROUP() {
  return getToken(Sparql11Parser::GROUP, 0);
}

tree::TerminalNode* Sparql11Parser::GroupClauseContext::BY() {
  return getToken(Sparql11Parser::BY, 0);
}

std::vector<Sparql11Parser::GroupConditionContext *> Sparql11Parser::GroupClauseContext::groupCondition() {
  return getRuleContexts<Sparql11Parser::GroupConditionContext>();
}

Sparql11Parser::GroupConditionContext* Sparql11Parser::GroupClauseContext::groupCondition(size_t i) {
  return getRuleContext<Sparql11Parser::GroupConditionContext>(i);
}


size_t Sparql11Parser::GroupClauseContext::getRuleIndex() const {
  return Sparql11Parser::RuleGroupClause;
}

antlrcpp::Any Sparql11Parser::GroupClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitGroupClause(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::GroupClauseContext* Sparql11Parser::groupClause() {
  GroupClauseContext *_localctx = _tracker.createInstance<GroupClauseContext>(_ctx, getState());
  enterRule(_localctx, 34, Sparql11Parser::RuleGroupClause);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(369);
    match(Sparql11Parser::GROUP);
    setState(370);
    match(Sparql11Parser::BY);
    setState(372); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(371);
      groupCondition();
      setState(374); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << Sparql11Parser::EXISTS)
      | (1ULL << Sparql11Parser::COALESCE)
      | (1ULL << Sparql11Parser::IF)
      | (1ULL << Sparql11Parser::NOT)
      | (1ULL << Sparql11Parser::STR)
      | (1ULL << Sparql11Parser::LANG)
      | (1ULL << Sparql11Parser::LANGMATCHES)
      | (1ULL << Sparql11Parser::DATATYPE)
      | (1ULL << Sparql11Parser::BOUND)
      | (1ULL << Sparql11Parser::SAMETERM))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (Sparql11Parser::IRI - 64))
      | (1ULL << (Sparql11Parser::URI - 64))
      | (1ULL << (Sparql11Parser::BNODE - 64))
      | (1ULL << (Sparql11Parser::STRLANG - 64))
      | (1ULL << (Sparql11Parser::STRDT - 64))
      | (1ULL << (Sparql11Parser::ISIRI - 64))
      | (1ULL << (Sparql11Parser::ISURI - 64))
      | (1ULL << (Sparql11Parser::ISBLANK - 64))
      | (1ULL << (Sparql11Parser::ISLITERAL - 64))
      | (1ULL << (Sparql11Parser::ISNUMERIC - 64))
      | (1ULL << (Sparql11Parser::REGEX - 64))
      | (1ULL << (Sparql11Parser::IRI_REF - 64))
      | (1ULL << (Sparql11Parser::PNAME_NS - 64))
      | (1ULL << (Sparql11Parser::PNAME_LN - 64))
      | (1ULL << (Sparql11Parser::VAR1 - 64))
      | (1ULL << (Sparql11Parser::VAR2 - 64))
      | (1ULL << (Sparql11Parser::OPEN_BRACE - 64)))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GroupConditionContext ------------------------------------------------------------------

Sparql11Parser::GroupConditionContext::GroupConditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::BuiltInCallContext* Sparql11Parser::GroupConditionContext::builtInCall() {
  return getRuleContext<Sparql11Parser::BuiltInCallContext>(0);
}

Sparql11Parser::FunctionCallContext* Sparql11Parser::GroupConditionContext::functionCall() {
  return getRuleContext<Sparql11Parser::FunctionCallContext>(0);
}

tree::TerminalNode* Sparql11Parser::GroupConditionContext::OPEN_BRACE() {
  return getToken(Sparql11Parser::OPEN_BRACE, 0);
}

Sparql11Parser::ExpressionContext* Sparql11Parser::GroupConditionContext::expression() {
  return getRuleContext<Sparql11Parser::ExpressionContext>(0);
}

tree::TerminalNode* Sparql11Parser::GroupConditionContext::CLOSE_BRACE() {
  return getToken(Sparql11Parser::CLOSE_BRACE, 0);
}

tree::TerminalNode* Sparql11Parser::GroupConditionContext::AS() {
  return getToken(Sparql11Parser::AS, 0);
}

Sparql11Parser::VariableContext* Sparql11Parser::GroupConditionContext::variable() {
  return getRuleContext<Sparql11Parser::VariableContext>(0);
}


size_t Sparql11Parser::GroupConditionContext::getRuleIndex() const {
  return Sparql11Parser::RuleGroupCondition;
}

antlrcpp::Any Sparql11Parser::GroupConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitGroupCondition(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::GroupConditionContext* Sparql11Parser::groupCondition() {
  GroupConditionContext *_localctx = _tracker.createInstance<GroupConditionContext>(_ctx, getState());
  enterRule(_localctx, 36, Sparql11Parser::RuleGroupCondition);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(387);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::EXISTS:
      case Sparql11Parser::COALESCE:
      case Sparql11Parser::IF:
      case Sparql11Parser::NOT:
      case Sparql11Parser::STR:
      case Sparql11Parser::LANG:
      case Sparql11Parser::LANGMATCHES:
      case Sparql11Parser::DATATYPE:
      case Sparql11Parser::BOUND:
      case Sparql11Parser::SAMETERM:
      case Sparql11Parser::IRI:
      case Sparql11Parser::URI:
      case Sparql11Parser::BNODE:
      case Sparql11Parser::STRLANG:
      case Sparql11Parser::STRDT:
      case Sparql11Parser::ISIRI:
      case Sparql11Parser::ISURI:
      case Sparql11Parser::ISBLANK:
      case Sparql11Parser::ISLITERAL:
      case Sparql11Parser::ISNUMERIC:
      case Sparql11Parser::REGEX: {
        enterOuterAlt(_localctx, 1);
        setState(376);
        builtInCall();
        break;
      }

      case Sparql11Parser::IRI_REF:
      case Sparql11Parser::PNAME_NS:
      case Sparql11Parser::PNAME_LN: {
        enterOuterAlt(_localctx, 2);
        setState(377);
        functionCall();
        break;
      }

      case Sparql11Parser::OPEN_BRACE: {
        enterOuterAlt(_localctx, 3);
        setState(378);
        match(Sparql11Parser::OPEN_BRACE);
        setState(379);
        expression();
        setState(382);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == Sparql11Parser::AS) {
          setState(380);
          match(Sparql11Parser::AS);
          setState(381);
          variable();
        }
        setState(384);
        match(Sparql11Parser::CLOSE_BRACE);
        break;
      }

      case Sparql11Parser::VAR1:
      case Sparql11Parser::VAR2: {
        enterOuterAlt(_localctx, 4);
        setState(386);
        variable();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- HavingClauseContext ------------------------------------------------------------------

Sparql11Parser::HavingClauseContext::HavingClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::HavingClauseContext::HAVING() {
  return getToken(Sparql11Parser::HAVING, 0);
}

std::vector<Sparql11Parser::HavingConditionContext *> Sparql11Parser::HavingClauseContext::havingCondition() {
  return getRuleContexts<Sparql11Parser::HavingConditionContext>();
}

Sparql11Parser::HavingConditionContext* Sparql11Parser::HavingClauseContext::havingCondition(size_t i) {
  return getRuleContext<Sparql11Parser::HavingConditionContext>(i);
}


size_t Sparql11Parser::HavingClauseContext::getRuleIndex() const {
  return Sparql11Parser::RuleHavingClause;
}

antlrcpp::Any Sparql11Parser::HavingClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitHavingClause(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::HavingClauseContext* Sparql11Parser::havingClause() {
  HavingClauseContext *_localctx = _tracker.createInstance<HavingClauseContext>(_ctx, getState());
  enterRule(_localctx, 38, Sparql11Parser::RuleHavingClause);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(389);
    match(Sparql11Parser::HAVING);
    setState(391); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(390);
      havingCondition();
      setState(393); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << Sparql11Parser::EXISTS)
      | (1ULL << Sparql11Parser::COALESCE)
      | (1ULL << Sparql11Parser::IF)
      | (1ULL << Sparql11Parser::NOT)
      | (1ULL << Sparql11Parser::STR)
      | (1ULL << Sparql11Parser::LANG)
      | (1ULL << Sparql11Parser::LANGMATCHES)
      | (1ULL << Sparql11Parser::DATATYPE)
      | (1ULL << Sparql11Parser::BOUND)
      | (1ULL << Sparql11Parser::SAMETERM))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (Sparql11Parser::IRI - 64))
      | (1ULL << (Sparql11Parser::URI - 64))
      | (1ULL << (Sparql11Parser::BNODE - 64))
      | (1ULL << (Sparql11Parser::STRLANG - 64))
      | (1ULL << (Sparql11Parser::STRDT - 64))
      | (1ULL << (Sparql11Parser::ISIRI - 64))
      | (1ULL << (Sparql11Parser::ISURI - 64))
      | (1ULL << (Sparql11Parser::ISBLANK - 64))
      | (1ULL << (Sparql11Parser::ISLITERAL - 64))
      | (1ULL << (Sparql11Parser::ISNUMERIC - 64))
      | (1ULL << (Sparql11Parser::REGEX - 64))
      | (1ULL << (Sparql11Parser::IRI_REF - 64))
      | (1ULL << (Sparql11Parser::PNAME_NS - 64))
      | (1ULL << (Sparql11Parser::PNAME_LN - 64))
      | (1ULL << (Sparql11Parser::OPEN_BRACE - 64)))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- HavingConditionContext ------------------------------------------------------------------

Sparql11Parser::HavingConditionContext::HavingConditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::ConstraintContext* Sparql11Parser::HavingConditionContext::constraint() {
  return getRuleContext<Sparql11Parser::ConstraintContext>(0);
}


size_t Sparql11Parser::HavingConditionContext::getRuleIndex() const {
  return Sparql11Parser::RuleHavingCondition;
}

antlrcpp::Any Sparql11Parser::HavingConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitHavingCondition(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::HavingConditionContext* Sparql11Parser::havingCondition() {
  HavingConditionContext *_localctx = _tracker.createInstance<HavingConditionContext>(_ctx, getState());
  enterRule(_localctx, 40, Sparql11Parser::RuleHavingCondition);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(395);
    constraint();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OrderClauseContext ------------------------------------------------------------------

Sparql11Parser::OrderClauseContext::OrderClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::OrderClauseContext::ORDER() {
  return getToken(Sparql11Parser::ORDER, 0);
}

tree::TerminalNode* Sparql11Parser::OrderClauseContext::BY() {
  return getToken(Sparql11Parser::BY, 0);
}

std::vector<Sparql11Parser::OrderConditionContext *> Sparql11Parser::OrderClauseContext::orderCondition() {
  return getRuleContexts<Sparql11Parser::OrderConditionContext>();
}

Sparql11Parser::OrderConditionContext* Sparql11Parser::OrderClauseContext::orderCondition(size_t i) {
  return getRuleContext<Sparql11Parser::OrderConditionContext>(i);
}


size_t Sparql11Parser::OrderClauseContext::getRuleIndex() const {
  return Sparql11Parser::RuleOrderClause;
}

antlrcpp::Any Sparql11Parser::OrderClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitOrderClause(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::OrderClauseContext* Sparql11Parser::orderClause() {
  OrderClauseContext *_localctx = _tracker.createInstance<OrderClauseContext>(_ctx, getState());
  enterRule(_localctx, 42, Sparql11Parser::RuleOrderClause);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(397);
    match(Sparql11Parser::ORDER);
    setState(398);
    match(Sparql11Parser::BY);
    setState(400); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(399);
      orderCondition();
      setState(402); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << Sparql11Parser::EXISTS)
      | (1ULL << Sparql11Parser::COALESCE)
      | (1ULL << Sparql11Parser::IF)
      | (1ULL << Sparql11Parser::NOT)
      | (1ULL << Sparql11Parser::ASC)
      | (1ULL << Sparql11Parser::DESC)
      | (1ULL << Sparql11Parser::STR)
      | (1ULL << Sparql11Parser::LANG)
      | (1ULL << Sparql11Parser::LANGMATCHES)
      | (1ULL << Sparql11Parser::DATATYPE)
      | (1ULL << Sparql11Parser::BOUND)
      | (1ULL << Sparql11Parser::SAMETERM))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (Sparql11Parser::IRI - 64))
      | (1ULL << (Sparql11Parser::URI - 64))
      | (1ULL << (Sparql11Parser::BNODE - 64))
      | (1ULL << (Sparql11Parser::STRLANG - 64))
      | (1ULL << (Sparql11Parser::STRDT - 64))
      | (1ULL << (Sparql11Parser::ISIRI - 64))
      | (1ULL << (Sparql11Parser::ISURI - 64))
      | (1ULL << (Sparql11Parser::ISBLANK - 64))
      | (1ULL << (Sparql11Parser::ISLITERAL - 64))
      | (1ULL << (Sparql11Parser::ISNUMERIC - 64))
      | (1ULL << (Sparql11Parser::REGEX - 64))
      | (1ULL << (Sparql11Parser::IRI_REF - 64))
      | (1ULL << (Sparql11Parser::PNAME_NS - 64))
      | (1ULL << (Sparql11Parser::PNAME_LN - 64))
      | (1ULL << (Sparql11Parser::VAR1 - 64))
      | (1ULL << (Sparql11Parser::VAR2 - 64))
      | (1ULL << (Sparql11Parser::OPEN_BRACE - 64)))) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OrderConditionContext ------------------------------------------------------------------

Sparql11Parser::OrderConditionContext::OrderConditionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::BrackettedExpressionContext* Sparql11Parser::OrderConditionContext::brackettedExpression() {
  return getRuleContext<Sparql11Parser::BrackettedExpressionContext>(0);
}

tree::TerminalNode* Sparql11Parser::OrderConditionContext::ASC() {
  return getToken(Sparql11Parser::ASC, 0);
}

tree::TerminalNode* Sparql11Parser::OrderConditionContext::DESC() {
  return getToken(Sparql11Parser::DESC, 0);
}

Sparql11Parser::ConstraintContext* Sparql11Parser::OrderConditionContext::constraint() {
  return getRuleContext<Sparql11Parser::ConstraintContext>(0);
}

Sparql11Parser::VariableContext* Sparql11Parser::OrderConditionContext::variable() {
  return getRuleContext<Sparql11Parser::VariableContext>(0);
}


size_t Sparql11Parser::OrderConditionContext::getRuleIndex() const {
  return Sparql11Parser::RuleOrderCondition;
}

antlrcpp::Any Sparql11Parser::OrderConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitOrderCondition(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::OrderConditionContext* Sparql11Parser::orderCondition() {
  OrderConditionContext *_localctx = _tracker.createInstance<OrderConditionContext>(_ctx, getState());
  enterRule(_localctx, 44, Sparql11Parser::RuleOrderCondition);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(410);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::ASC:
      case Sparql11Parser::DESC: {
        enterOuterAlt(_localctx, 1);
        setState(404);
        _la = _input->LA(1);
        if (!(_la == Sparql11Parser::ASC

        || _la == Sparql11Parser::DESC)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(405);
        brackettedExpression();
        break;
      }

      case Sparql11Parser::EXISTS:
      case Sparql11Parser::COALESCE:
      case Sparql11Parser::IF:
      case Sparql11Parser::NOT:
      case Sparql11Parser::STR:
      case Sparql11Parser::LANG:
      case Sparql11Parser::LANGMATCHES:
      case Sparql11Parser::DATATYPE:
      case Sparql11Parser::BOUND:
      case Sparql11Parser::SAMETERM:
      case Sparql11Parser::IRI:
      case Sparql11Parser::URI:
      case Sparql11Parser::BNODE:
      case Sparql11Parser::STRLANG:
      case Sparql11Parser::STRDT:
      case Sparql11Parser::ISIRI:
      case Sparql11Parser::ISURI:
      case Sparql11Parser::ISBLANK:
      case Sparql11Parser::ISLITERAL:
      case Sparql11Parser::ISNUMERIC:
      case Sparql11Parser::REGEX:
      case Sparql11Parser::IRI_REF:
      case Sparql11Parser::PNAME_NS:
      case Sparql11Parser::PNAME_LN:
      case Sparql11Parser::VAR1:
      case Sparql11Parser::VAR2:
      case Sparql11Parser::OPEN_BRACE: {
        enterOuterAlt(_localctx, 2);
        setState(408);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case Sparql11Parser::EXISTS:
          case Sparql11Parser::COALESCE:
          case Sparql11Parser::IF:
          case Sparql11Parser::NOT:
          case Sparql11Parser::STR:
          case Sparql11Parser::LANG:
          case Sparql11Parser::LANGMATCHES:
          case Sparql11Parser::DATATYPE:
          case Sparql11Parser::BOUND:
          case Sparql11Parser::SAMETERM:
          case Sparql11Parser::IRI:
          case Sparql11Parser::URI:
          case Sparql11Parser::BNODE:
          case Sparql11Parser::STRLANG:
          case Sparql11Parser::STRDT:
          case Sparql11Parser::ISIRI:
          case Sparql11Parser::ISURI:
          case Sparql11Parser::ISBLANK:
          case Sparql11Parser::ISLITERAL:
          case Sparql11Parser::ISNUMERIC:
          case Sparql11Parser::REGEX:
          case Sparql11Parser::IRI_REF:
          case Sparql11Parser::PNAME_NS:
          case Sparql11Parser::PNAME_LN:
          case Sparql11Parser::OPEN_BRACE: {
            setState(406);
            constraint();
            break;
          }

          case Sparql11Parser::VAR1:
          case Sparql11Parser::VAR2: {
            setState(407);
            variable();
            break;
          }

        default:
          throw NoViableAltException(this);
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LimitOffsetClausesContext ------------------------------------------------------------------

Sparql11Parser::LimitOffsetClausesContext::LimitOffsetClausesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::LimitClauseContext* Sparql11Parser::LimitOffsetClausesContext::limitClause() {
  return getRuleContext<Sparql11Parser::LimitClauseContext>(0);
}

Sparql11Parser::OffsetClauseContext* Sparql11Parser::LimitOffsetClausesContext::offsetClause() {
  return getRuleContext<Sparql11Parser::OffsetClauseContext>(0);
}


size_t Sparql11Parser::LimitOffsetClausesContext::getRuleIndex() const {
  return Sparql11Parser::RuleLimitOffsetClauses;
}

antlrcpp::Any Sparql11Parser::LimitOffsetClausesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitLimitOffsetClauses(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::LimitOffsetClausesContext* Sparql11Parser::limitOffsetClauses() {
  LimitOffsetClausesContext *_localctx = _tracker.createInstance<LimitOffsetClausesContext>(_ctx, getState());
  enterRule(_localctx, 46, Sparql11Parser::RuleLimitOffsetClauses);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(420);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::LIMIT: {
        enterOuterAlt(_localctx, 1);
        setState(412);
        limitClause();
        setState(414);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == Sparql11Parser::OFFSET) {
          setState(413);
          offsetClause();
        }
        break;
      }

      case Sparql11Parser::OFFSET: {
        enterOuterAlt(_localctx, 2);
        setState(416);
        offsetClause();
        setState(418);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == Sparql11Parser::LIMIT) {
          setState(417);
          limitClause();
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LimitClauseContext ------------------------------------------------------------------

Sparql11Parser::LimitClauseContext::LimitClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::LimitClauseContext::LIMIT() {
  return getToken(Sparql11Parser::LIMIT, 0);
}

tree::TerminalNode* Sparql11Parser::LimitClauseContext::INTEGER() {
  return getToken(Sparql11Parser::INTEGER, 0);
}


size_t Sparql11Parser::LimitClauseContext::getRuleIndex() const {
  return Sparql11Parser::RuleLimitClause;
}

antlrcpp::Any Sparql11Parser::LimitClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitLimitClause(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::LimitClauseContext* Sparql11Parser::limitClause() {
  LimitClauseContext *_localctx = _tracker.createInstance<LimitClauseContext>(_ctx, getState());
  enterRule(_localctx, 48, Sparql11Parser::RuleLimitClause);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(422);
    match(Sparql11Parser::LIMIT);
    setState(423);
    match(Sparql11Parser::INTEGER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OffsetClauseContext ------------------------------------------------------------------

Sparql11Parser::OffsetClauseContext::OffsetClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::OffsetClauseContext::OFFSET() {
  return getToken(Sparql11Parser::OFFSET, 0);
}

tree::TerminalNode* Sparql11Parser::OffsetClauseContext::INTEGER() {
  return getToken(Sparql11Parser::INTEGER, 0);
}


size_t Sparql11Parser::OffsetClauseContext::getRuleIndex() const {
  return Sparql11Parser::RuleOffsetClause;
}

antlrcpp::Any Sparql11Parser::OffsetClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitOffsetClause(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::OffsetClauseContext* Sparql11Parser::offsetClause() {
  OffsetClauseContext *_localctx = _tracker.createInstance<OffsetClauseContext>(_ctx, getState());
  enterRule(_localctx, 50, Sparql11Parser::RuleOffsetClause);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(425);
    match(Sparql11Parser::OFFSET);
    setState(426);
    match(Sparql11Parser::INTEGER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BindingsClauseContext ------------------------------------------------------------------

Sparql11Parser::BindingsClauseContext::BindingsClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::BindingsClauseContext::BINDINGS() {
  return getToken(Sparql11Parser::BINDINGS, 0);
}

tree::TerminalNode* Sparql11Parser::BindingsClauseContext::OPEN_CURLY_BRACE() {
  return getToken(Sparql11Parser::OPEN_CURLY_BRACE, 0);
}

tree::TerminalNode* Sparql11Parser::BindingsClauseContext::CLOSE_CURLY_BRACE() {
  return getToken(Sparql11Parser::CLOSE_CURLY_BRACE, 0);
}

std::vector<Sparql11Parser::VariableContext *> Sparql11Parser::BindingsClauseContext::variable() {
  return getRuleContexts<Sparql11Parser::VariableContext>();
}

Sparql11Parser::VariableContext* Sparql11Parser::BindingsClauseContext::variable(size_t i) {
  return getRuleContext<Sparql11Parser::VariableContext>(i);
}

std::vector<tree::TerminalNode *> Sparql11Parser::BindingsClauseContext::OPEN_BRACE() {
  return getTokens(Sparql11Parser::OPEN_BRACE);
}

tree::TerminalNode* Sparql11Parser::BindingsClauseContext::OPEN_BRACE(size_t i) {
  return getToken(Sparql11Parser::OPEN_BRACE, i);
}

std::vector<tree::TerminalNode *> Sparql11Parser::BindingsClauseContext::CLOSE_BRACE() {
  return getTokens(Sparql11Parser::CLOSE_BRACE);
}

tree::TerminalNode* Sparql11Parser::BindingsClauseContext::CLOSE_BRACE(size_t i) {
  return getToken(Sparql11Parser::CLOSE_BRACE, i);
}

std::vector<Sparql11Parser::BindingValueContext *> Sparql11Parser::BindingsClauseContext::bindingValue() {
  return getRuleContexts<Sparql11Parser::BindingValueContext>();
}

Sparql11Parser::BindingValueContext* Sparql11Parser::BindingsClauseContext::bindingValue(size_t i) {
  return getRuleContext<Sparql11Parser::BindingValueContext>(i);
}

std::vector<tree::TerminalNode *> Sparql11Parser::BindingsClauseContext::WS() {
  return getTokens(Sparql11Parser::WS);
}

tree::TerminalNode* Sparql11Parser::BindingsClauseContext::WS(size_t i) {
  return getToken(Sparql11Parser::WS, i);
}


size_t Sparql11Parser::BindingsClauseContext::getRuleIndex() const {
  return Sparql11Parser::RuleBindingsClause;
}

antlrcpp::Any Sparql11Parser::BindingsClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitBindingsClause(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::BindingsClauseContext* Sparql11Parser::bindingsClause() {
  BindingsClauseContext *_localctx = _tracker.createInstance<BindingsClauseContext>(_ctx, getState());
  enterRule(_localctx, 52, Sparql11Parser::RuleBindingsClause);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(458);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Sparql11Parser::BINDINGS) {
      setState(428);
      match(Sparql11Parser::BINDINGS);
      setState(432);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == Sparql11Parser::VAR1

      || _la == Sparql11Parser::VAR2) {
        setState(429);
        variable();
        setState(434);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(435);
      match(Sparql11Parser::OPEN_CURLY_BRACE);
      setState(454);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == Sparql11Parser::OPEN_BRACE) {
        setState(452);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 33, _ctx)) {
        case 1: {
          setState(436);
          match(Sparql11Parser::OPEN_BRACE);
          setState(438); 
          _errHandler->sync(this);
          _la = _input->LA(1);
          do {
            setState(437);
            bindingValue();
            setState(440); 
            _errHandler->sync(this);
            _la = _input->LA(1);
          } while (((((_la - 75) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 75)) & ((1ULL << (Sparql11Parser::TRUE - 75))
            | (1ULL << (Sparql11Parser::FALSE - 75))
            | (1ULL << (Sparql11Parser::IRI_REF - 75))
            | (1ULL << (Sparql11Parser::PNAME_NS - 75))
            | (1ULL << (Sparql11Parser::PNAME_LN - 75))
            | (1ULL << (Sparql11Parser::INTEGER - 75))
            | (1ULL << (Sparql11Parser::DECIMAL - 75))
            | (1ULL << (Sparql11Parser::DOUBLE - 75))
            | (1ULL << (Sparql11Parser::INTEGER_POSITIVE - 75))
            | (1ULL << (Sparql11Parser::DECIMAL_POSITIVE - 75))
            | (1ULL << (Sparql11Parser::DOUBLE_POSITIVE - 75))
            | (1ULL << (Sparql11Parser::INTEGER_NEGATIVE - 75))
            | (1ULL << (Sparql11Parser::DECIMAL_NEGATIVE - 75))
            | (1ULL << (Sparql11Parser::DOUBLE_NEGATIVE - 75))
            | (1ULL << (Sparql11Parser::STRING_LITERAL1 - 75))
            | (1ULL << (Sparql11Parser::STRING_LITERAL2 - 75))
            | (1ULL << (Sparql11Parser::STRING_LITERAL_LONG1 - 75))
            | (1ULL << (Sparql11Parser::STRING_LITERAL_LONG2 - 75))
            | (1ULL << (Sparql11Parser::UNDEF - 75)))) != 0));
          setState(442);
          match(Sparql11Parser::CLOSE_BRACE);
          break;
        }

        case 2: {
          setState(444);
          match(Sparql11Parser::OPEN_BRACE);
          setState(448);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == Sparql11Parser::WS) {
            setState(445);
            match(Sparql11Parser::WS);
            setState(450);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
          setState(451);
          match(Sparql11Parser::CLOSE_BRACE);
          break;
        }

        }
        setState(456);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(457);
      match(Sparql11Parser::CLOSE_CURLY_BRACE);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BindingValueContext ------------------------------------------------------------------

Sparql11Parser::BindingValueContext::BindingValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::IriRefContext* Sparql11Parser::BindingValueContext::iriRef() {
  return getRuleContext<Sparql11Parser::IriRefContext>(0);
}

Sparql11Parser::RdfLiteralContext* Sparql11Parser::BindingValueContext::rdfLiteral() {
  return getRuleContext<Sparql11Parser::RdfLiteralContext>(0);
}

Sparql11Parser::NumericLiteralContext* Sparql11Parser::BindingValueContext::numericLiteral() {
  return getRuleContext<Sparql11Parser::NumericLiteralContext>(0);
}

Sparql11Parser::BooleanLiteralContext* Sparql11Parser::BindingValueContext::booleanLiteral() {
  return getRuleContext<Sparql11Parser::BooleanLiteralContext>(0);
}

tree::TerminalNode* Sparql11Parser::BindingValueContext::UNDEF() {
  return getToken(Sparql11Parser::UNDEF, 0);
}


size_t Sparql11Parser::BindingValueContext::getRuleIndex() const {
  return Sparql11Parser::RuleBindingValue;
}

antlrcpp::Any Sparql11Parser::BindingValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitBindingValue(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::BindingValueContext* Sparql11Parser::bindingValue() {
  BindingValueContext *_localctx = _tracker.createInstance<BindingValueContext>(_ctx, getState());
  enterRule(_localctx, 54, Sparql11Parser::RuleBindingValue);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(465);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::IRI_REF:
      case Sparql11Parser::PNAME_NS:
      case Sparql11Parser::PNAME_LN: {
        enterOuterAlt(_localctx, 1);
        setState(460);
        iriRef();
        break;
      }

      case Sparql11Parser::STRING_LITERAL1:
      case Sparql11Parser::STRING_LITERAL2:
      case Sparql11Parser::STRING_LITERAL_LONG1:
      case Sparql11Parser::STRING_LITERAL_LONG2: {
        enterOuterAlt(_localctx, 2);
        setState(461);
        rdfLiteral();
        break;
      }

      case Sparql11Parser::INTEGER:
      case Sparql11Parser::DECIMAL:
      case Sparql11Parser::DOUBLE:
      case Sparql11Parser::INTEGER_POSITIVE:
      case Sparql11Parser::DECIMAL_POSITIVE:
      case Sparql11Parser::DOUBLE_POSITIVE:
      case Sparql11Parser::INTEGER_NEGATIVE:
      case Sparql11Parser::DECIMAL_NEGATIVE:
      case Sparql11Parser::DOUBLE_NEGATIVE: {
        enterOuterAlt(_localctx, 3);
        setState(462);
        numericLiteral();
        break;
      }

      case Sparql11Parser::TRUE:
      case Sparql11Parser::FALSE: {
        enterOuterAlt(_localctx, 4);
        setState(463);
        booleanLiteral();
        break;
      }

      case Sparql11Parser::UNDEF: {
        enterOuterAlt(_localctx, 5);
        setState(464);
        match(Sparql11Parser::UNDEF);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UpdateUnitContext ------------------------------------------------------------------

Sparql11Parser::UpdateUnitContext::UpdateUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::UpdateContext* Sparql11Parser::UpdateUnitContext::update() {
  return getRuleContext<Sparql11Parser::UpdateContext>(0);
}


size_t Sparql11Parser::UpdateUnitContext::getRuleIndex() const {
  return Sparql11Parser::RuleUpdateUnit;
}

antlrcpp::Any Sparql11Parser::UpdateUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitUpdateUnit(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::UpdateUnitContext* Sparql11Parser::updateUnit() {
  UpdateUnitContext *_localctx = _tracker.createInstance<UpdateUnitContext>(_ctx, getState());
  enterRule(_localctx, 56, Sparql11Parser::RuleUpdateUnit);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(467);
    update();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UpdateContext ------------------------------------------------------------------

Sparql11Parser::UpdateContext::UpdateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::PrologueContext* Sparql11Parser::UpdateContext::prologue() {
  return getRuleContext<Sparql11Parser::PrologueContext>(0);
}

Sparql11Parser::Update1Context* Sparql11Parser::UpdateContext::update1() {
  return getRuleContext<Sparql11Parser::Update1Context>(0);
}

tree::TerminalNode* Sparql11Parser::UpdateContext::SEMICOLON() {
  return getToken(Sparql11Parser::SEMICOLON, 0);
}

Sparql11Parser::UpdateContext* Sparql11Parser::UpdateContext::update() {
  return getRuleContext<Sparql11Parser::UpdateContext>(0);
}


size_t Sparql11Parser::UpdateContext::getRuleIndex() const {
  return Sparql11Parser::RuleUpdate;
}

antlrcpp::Any Sparql11Parser::UpdateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitUpdate(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::UpdateContext* Sparql11Parser::update() {
  UpdateContext *_localctx = _tracker.createInstance<UpdateContext>(_ctx, getState());
  enterRule(_localctx, 58, Sparql11Parser::RuleUpdate);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(469);
    prologue();
    setState(470);
    update1();
    setState(473);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Sparql11Parser::SEMICOLON) {
      setState(471);
      match(Sparql11Parser::SEMICOLON);
      setState(472);
      update();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Update1Context ------------------------------------------------------------------

Sparql11Parser::Update1Context::Update1Context(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::LoadContext* Sparql11Parser::Update1Context::load() {
  return getRuleContext<Sparql11Parser::LoadContext>(0);
}

Sparql11Parser::ClearContext* Sparql11Parser::Update1Context::clear() {
  return getRuleContext<Sparql11Parser::ClearContext>(0);
}

Sparql11Parser::DropContext* Sparql11Parser::Update1Context::drop() {
  return getRuleContext<Sparql11Parser::DropContext>(0);
}

Sparql11Parser::CreateContext* Sparql11Parser::Update1Context::create() {
  return getRuleContext<Sparql11Parser::CreateContext>(0);
}

Sparql11Parser::InsertDataContext* Sparql11Parser::Update1Context::insertData() {
  return getRuleContext<Sparql11Parser::InsertDataContext>(0);
}

Sparql11Parser::DeleteDataContext* Sparql11Parser::Update1Context::deleteData() {
  return getRuleContext<Sparql11Parser::DeleteDataContext>(0);
}

Sparql11Parser::DeleteWhereContext* Sparql11Parser::Update1Context::deleteWhere() {
  return getRuleContext<Sparql11Parser::DeleteWhereContext>(0);
}

Sparql11Parser::ModifyContext* Sparql11Parser::Update1Context::modify() {
  return getRuleContext<Sparql11Parser::ModifyContext>(0);
}


size_t Sparql11Parser::Update1Context::getRuleIndex() const {
  return Sparql11Parser::RuleUpdate1;
}

antlrcpp::Any Sparql11Parser::Update1Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitUpdate1(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::Update1Context* Sparql11Parser::update1() {
  Update1Context *_localctx = _tracker.createInstance<Update1Context>(_ctx, getState());
  enterRule(_localctx, 60, Sparql11Parser::RuleUpdate1);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(484);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 38, _ctx)) {
    case 1: {
      break;
    }

    case 2: {
      setState(476);
      load();
      break;
    }

    case 3: {
      setState(477);
      clear();
      break;
    }

    case 4: {
      setState(478);
      drop();
      break;
    }

    case 5: {
      setState(479);
      create();
      break;
    }

    case 6: {
      setState(480);
      insertData();
      break;
    }

    case 7: {
      setState(481);
      deleteData();
      break;
    }

    case 8: {
      setState(482);
      deleteWhere();
      break;
    }

    case 9: {
      setState(483);
      modify();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LoadContext ------------------------------------------------------------------

Sparql11Parser::LoadContext::LoadContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::LoadContext::LOAD() {
  return getToken(Sparql11Parser::LOAD, 0);
}

Sparql11Parser::IriRefContext* Sparql11Parser::LoadContext::iriRef() {
  return getRuleContext<Sparql11Parser::IriRefContext>(0);
}

tree::TerminalNode* Sparql11Parser::LoadContext::INTO() {
  return getToken(Sparql11Parser::INTO, 0);
}

Sparql11Parser::GraphRefContext* Sparql11Parser::LoadContext::graphRef() {
  return getRuleContext<Sparql11Parser::GraphRefContext>(0);
}


size_t Sparql11Parser::LoadContext::getRuleIndex() const {
  return Sparql11Parser::RuleLoad;
}

antlrcpp::Any Sparql11Parser::LoadContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitLoad(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::LoadContext* Sparql11Parser::load() {
  LoadContext *_localctx = _tracker.createInstance<LoadContext>(_ctx, getState());
  enterRule(_localctx, 62, Sparql11Parser::RuleLoad);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(486);
    match(Sparql11Parser::LOAD);
    setState(487);
    iriRef();
    setState(490);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Sparql11Parser::INTO) {
      setState(488);
      match(Sparql11Parser::INTO);
      setState(489);
      graphRef();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClearContext ------------------------------------------------------------------

Sparql11Parser::ClearContext::ClearContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::ClearContext::CLEAR() {
  return getToken(Sparql11Parser::CLEAR, 0);
}

Sparql11Parser::GraphRefAllContext* Sparql11Parser::ClearContext::graphRefAll() {
  return getRuleContext<Sparql11Parser::GraphRefAllContext>(0);
}

tree::TerminalNode* Sparql11Parser::ClearContext::SILENT() {
  return getToken(Sparql11Parser::SILENT, 0);
}


size_t Sparql11Parser::ClearContext::getRuleIndex() const {
  return Sparql11Parser::RuleClear;
}

antlrcpp::Any Sparql11Parser::ClearContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitClear(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::ClearContext* Sparql11Parser::clear() {
  ClearContext *_localctx = _tracker.createInstance<ClearContext>(_ctx, getState());
  enterRule(_localctx, 64, Sparql11Parser::RuleClear);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(492);
    match(Sparql11Parser::CLEAR);
    setState(494);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Sparql11Parser::SILENT) {
      setState(493);
      match(Sparql11Parser::SILENT);
    }
    setState(496);
    graphRefAll();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DropContext ------------------------------------------------------------------

Sparql11Parser::DropContext::DropContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::DropContext::DROP() {
  return getToken(Sparql11Parser::DROP, 0);
}

Sparql11Parser::GraphRefAllContext* Sparql11Parser::DropContext::graphRefAll() {
  return getRuleContext<Sparql11Parser::GraphRefAllContext>(0);
}

tree::TerminalNode* Sparql11Parser::DropContext::SILENT() {
  return getToken(Sparql11Parser::SILENT, 0);
}


size_t Sparql11Parser::DropContext::getRuleIndex() const {
  return Sparql11Parser::RuleDrop;
}

antlrcpp::Any Sparql11Parser::DropContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitDrop(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::DropContext* Sparql11Parser::drop() {
  DropContext *_localctx = _tracker.createInstance<DropContext>(_ctx, getState());
  enterRule(_localctx, 66, Sparql11Parser::RuleDrop);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(498);
    match(Sparql11Parser::DROP);
    setState(500);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Sparql11Parser::SILENT) {
      setState(499);
      match(Sparql11Parser::SILENT);
    }
    setState(502);
    graphRefAll();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CreateContext ------------------------------------------------------------------

Sparql11Parser::CreateContext::CreateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::CreateContext::CREATE() {
  return getToken(Sparql11Parser::CREATE, 0);
}

Sparql11Parser::GraphRefContext* Sparql11Parser::CreateContext::graphRef() {
  return getRuleContext<Sparql11Parser::GraphRefContext>(0);
}

tree::TerminalNode* Sparql11Parser::CreateContext::SILENT() {
  return getToken(Sparql11Parser::SILENT, 0);
}


size_t Sparql11Parser::CreateContext::getRuleIndex() const {
  return Sparql11Parser::RuleCreate;
}

antlrcpp::Any Sparql11Parser::CreateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitCreate(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::CreateContext* Sparql11Parser::create() {
  CreateContext *_localctx = _tracker.createInstance<CreateContext>(_ctx, getState());
  enterRule(_localctx, 68, Sparql11Parser::RuleCreate);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(504);
    match(Sparql11Parser::CREATE);
    setState(506);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Sparql11Parser::SILENT) {
      setState(505);
      match(Sparql11Parser::SILENT);
    }
    setState(508);
    graphRef();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InsertDataContext ------------------------------------------------------------------

Sparql11Parser::InsertDataContext::InsertDataContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::InsertDataContext::INSERT() {
  return getToken(Sparql11Parser::INSERT, 0);
}

tree::TerminalNode* Sparql11Parser::InsertDataContext::COMMA() {
  return getToken(Sparql11Parser::COMMA, 0);
}

tree::TerminalNode* Sparql11Parser::InsertDataContext::DATA() {
  return getToken(Sparql11Parser::DATA, 0);
}

Sparql11Parser::QuadDataContext* Sparql11Parser::InsertDataContext::quadData() {
  return getRuleContext<Sparql11Parser::QuadDataContext>(0);
}


size_t Sparql11Parser::InsertDataContext::getRuleIndex() const {
  return Sparql11Parser::RuleInsertData;
}

antlrcpp::Any Sparql11Parser::InsertDataContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitInsertData(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::InsertDataContext* Sparql11Parser::insertData() {
  InsertDataContext *_localctx = _tracker.createInstance<InsertDataContext>(_ctx, getState());
  enterRule(_localctx, 70, Sparql11Parser::RuleInsertData);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(510);
    match(Sparql11Parser::INSERT);
    setState(511);
    match(Sparql11Parser::COMMA);
    setState(512);
    match(Sparql11Parser::DATA);
    setState(513);
    quadData();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeleteDataContext ------------------------------------------------------------------

Sparql11Parser::DeleteDataContext::DeleteDataContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::DeleteDataContext::DELETE() {
  return getToken(Sparql11Parser::DELETE, 0);
}

tree::TerminalNode* Sparql11Parser::DeleteDataContext::DATA() {
  return getToken(Sparql11Parser::DATA, 0);
}

Sparql11Parser::QuadDataContext* Sparql11Parser::DeleteDataContext::quadData() {
  return getRuleContext<Sparql11Parser::QuadDataContext>(0);
}


size_t Sparql11Parser::DeleteDataContext::getRuleIndex() const {
  return Sparql11Parser::RuleDeleteData;
}

antlrcpp::Any Sparql11Parser::DeleteDataContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitDeleteData(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::DeleteDataContext* Sparql11Parser::deleteData() {
  DeleteDataContext *_localctx = _tracker.createInstance<DeleteDataContext>(_ctx, getState());
  enterRule(_localctx, 72, Sparql11Parser::RuleDeleteData);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(515);
    match(Sparql11Parser::DELETE);
    setState(516);
    match(Sparql11Parser::DATA);
    setState(517);
    quadData();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeleteWhereContext ------------------------------------------------------------------

Sparql11Parser::DeleteWhereContext::DeleteWhereContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::DeleteWhereContext::DELETE() {
  return getToken(Sparql11Parser::DELETE, 0);
}

tree::TerminalNode* Sparql11Parser::DeleteWhereContext::WHERE() {
  return getToken(Sparql11Parser::WHERE, 0);
}

Sparql11Parser::QuadPatternContext* Sparql11Parser::DeleteWhereContext::quadPattern() {
  return getRuleContext<Sparql11Parser::QuadPatternContext>(0);
}


size_t Sparql11Parser::DeleteWhereContext::getRuleIndex() const {
  return Sparql11Parser::RuleDeleteWhere;
}

antlrcpp::Any Sparql11Parser::DeleteWhereContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitDeleteWhere(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::DeleteWhereContext* Sparql11Parser::deleteWhere() {
  DeleteWhereContext *_localctx = _tracker.createInstance<DeleteWhereContext>(_ctx, getState());
  enterRule(_localctx, 74, Sparql11Parser::RuleDeleteWhere);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(519);
    match(Sparql11Parser::DELETE);
    setState(520);
    match(Sparql11Parser::WHERE);
    setState(521);
    quadPattern();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ModifyContext ------------------------------------------------------------------

Sparql11Parser::ModifyContext::ModifyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::ModifyContext::WHERE() {
  return getToken(Sparql11Parser::WHERE, 0);
}

Sparql11Parser::GroupGraphPatternContext* Sparql11Parser::ModifyContext::groupGraphPattern() {
  return getRuleContext<Sparql11Parser::GroupGraphPatternContext>(0);
}

Sparql11Parser::DeleteClauseContext* Sparql11Parser::ModifyContext::deleteClause() {
  return getRuleContext<Sparql11Parser::DeleteClauseContext>(0);
}

Sparql11Parser::InsertClauseContext* Sparql11Parser::ModifyContext::insertClause() {
  return getRuleContext<Sparql11Parser::InsertClauseContext>(0);
}

tree::TerminalNode* Sparql11Parser::ModifyContext::WITH() {
  return getToken(Sparql11Parser::WITH, 0);
}

Sparql11Parser::IriRefContext* Sparql11Parser::ModifyContext::iriRef() {
  return getRuleContext<Sparql11Parser::IriRefContext>(0);
}

std::vector<Sparql11Parser::UsingClauseContext *> Sparql11Parser::ModifyContext::usingClause() {
  return getRuleContexts<Sparql11Parser::UsingClauseContext>();
}

Sparql11Parser::UsingClauseContext* Sparql11Parser::ModifyContext::usingClause(size_t i) {
  return getRuleContext<Sparql11Parser::UsingClauseContext>(i);
}


size_t Sparql11Parser::ModifyContext::getRuleIndex() const {
  return Sparql11Parser::RuleModify;
}

antlrcpp::Any Sparql11Parser::ModifyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitModify(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::ModifyContext* Sparql11Parser::modify() {
  ModifyContext *_localctx = _tracker.createInstance<ModifyContext>(_ctx, getState());
  enterRule(_localctx, 76, Sparql11Parser::RuleModify);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(525);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Sparql11Parser::WITH) {
      setState(523);
      match(Sparql11Parser::WITH);
      setState(524);
      iriRef();
    }
    setState(532);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::DELETE: {
        setState(527);
        deleteClause();
        setState(529);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == Sparql11Parser::INSERT) {
          setState(528);
          insertClause();
        }
        break;
      }

      case Sparql11Parser::INSERT: {
        setState(531);
        insertClause();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(537);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Sparql11Parser::USING) {
      setState(534);
      usingClause();
      setState(539);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(540);
    match(Sparql11Parser::WHERE);
    setState(541);
    groupGraphPattern();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeleteClauseContext ------------------------------------------------------------------

Sparql11Parser::DeleteClauseContext::DeleteClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::DeleteClauseContext::DELETE() {
  return getToken(Sparql11Parser::DELETE, 0);
}

Sparql11Parser::QuadPatternContext* Sparql11Parser::DeleteClauseContext::quadPattern() {
  return getRuleContext<Sparql11Parser::QuadPatternContext>(0);
}


size_t Sparql11Parser::DeleteClauseContext::getRuleIndex() const {
  return Sparql11Parser::RuleDeleteClause;
}

antlrcpp::Any Sparql11Parser::DeleteClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitDeleteClause(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::DeleteClauseContext* Sparql11Parser::deleteClause() {
  DeleteClauseContext *_localctx = _tracker.createInstance<DeleteClauseContext>(_ctx, getState());
  enterRule(_localctx, 78, Sparql11Parser::RuleDeleteClause);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(543);
    match(Sparql11Parser::DELETE);
    setState(544);
    quadPattern();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- InsertClauseContext ------------------------------------------------------------------

Sparql11Parser::InsertClauseContext::InsertClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::InsertClauseContext::INSERT() {
  return getToken(Sparql11Parser::INSERT, 0);
}

Sparql11Parser::QuadPatternContext* Sparql11Parser::InsertClauseContext::quadPattern() {
  return getRuleContext<Sparql11Parser::QuadPatternContext>(0);
}


size_t Sparql11Parser::InsertClauseContext::getRuleIndex() const {
  return Sparql11Parser::RuleInsertClause;
}

antlrcpp::Any Sparql11Parser::InsertClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitInsertClause(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::InsertClauseContext* Sparql11Parser::insertClause() {
  InsertClauseContext *_localctx = _tracker.createInstance<InsertClauseContext>(_ctx, getState());
  enterRule(_localctx, 80, Sparql11Parser::RuleInsertClause);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(546);
    match(Sparql11Parser::INSERT);
    setState(547);
    quadPattern();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UsingClauseContext ------------------------------------------------------------------

Sparql11Parser::UsingClauseContext::UsingClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::UsingClauseContext::USING() {
  return getToken(Sparql11Parser::USING, 0);
}

Sparql11Parser::IriRefContext* Sparql11Parser::UsingClauseContext::iriRef() {
  return getRuleContext<Sparql11Parser::IriRefContext>(0);
}

tree::TerminalNode* Sparql11Parser::UsingClauseContext::NAMED() {
  return getToken(Sparql11Parser::NAMED, 0);
}


size_t Sparql11Parser::UsingClauseContext::getRuleIndex() const {
  return Sparql11Parser::RuleUsingClause;
}

antlrcpp::Any Sparql11Parser::UsingClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitUsingClause(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::UsingClauseContext* Sparql11Parser::usingClause() {
  UsingClauseContext *_localctx = _tracker.createInstance<UsingClauseContext>(_ctx, getState());
  enterRule(_localctx, 82, Sparql11Parser::RuleUsingClause);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(549);
    match(Sparql11Parser::USING);
    setState(553);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::IRI_REF:
      case Sparql11Parser::PNAME_NS:
      case Sparql11Parser::PNAME_LN: {
        setState(550);
        iriRef();
        break;
      }

      case Sparql11Parser::NAMED: {
        setState(551);
        match(Sparql11Parser::NAMED);
        setState(552);
        iriRef();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GraphRefContext ------------------------------------------------------------------

Sparql11Parser::GraphRefContext::GraphRefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::GraphRefContext::GRAPH() {
  return getToken(Sparql11Parser::GRAPH, 0);
}

Sparql11Parser::IriRefContext* Sparql11Parser::GraphRefContext::iriRef() {
  return getRuleContext<Sparql11Parser::IriRefContext>(0);
}


size_t Sparql11Parser::GraphRefContext::getRuleIndex() const {
  return Sparql11Parser::RuleGraphRef;
}

antlrcpp::Any Sparql11Parser::GraphRefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitGraphRef(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::GraphRefContext* Sparql11Parser::graphRef() {
  GraphRefContext *_localctx = _tracker.createInstance<GraphRefContext>(_ctx, getState());
  enterRule(_localctx, 84, Sparql11Parser::RuleGraphRef);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(557);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::GRAPH: {
        enterOuterAlt(_localctx, 1);
        setState(555);
        match(Sparql11Parser::GRAPH);
        break;
      }

      case Sparql11Parser::IRI_REF:
      case Sparql11Parser::PNAME_NS:
      case Sparql11Parser::PNAME_LN: {
        enterOuterAlt(_localctx, 2);
        setState(556);
        iriRef();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GraphRefAllContext ------------------------------------------------------------------

Sparql11Parser::GraphRefAllContext::GraphRefAllContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::GraphRefContext* Sparql11Parser::GraphRefAllContext::graphRef() {
  return getRuleContext<Sparql11Parser::GraphRefContext>(0);
}

tree::TerminalNode* Sparql11Parser::GraphRefAllContext::DEFAULT() {
  return getToken(Sparql11Parser::DEFAULT, 0);
}

tree::TerminalNode* Sparql11Parser::GraphRefAllContext::NAMED() {
  return getToken(Sparql11Parser::NAMED, 0);
}

tree::TerminalNode* Sparql11Parser::GraphRefAllContext::ALL() {
  return getToken(Sparql11Parser::ALL, 0);
}


size_t Sparql11Parser::GraphRefAllContext::getRuleIndex() const {
  return Sparql11Parser::RuleGraphRefAll;
}

antlrcpp::Any Sparql11Parser::GraphRefAllContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitGraphRefAll(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::GraphRefAllContext* Sparql11Parser::graphRefAll() {
  GraphRefAllContext *_localctx = _tracker.createInstance<GraphRefAllContext>(_ctx, getState());
  enterRule(_localctx, 86, Sparql11Parser::RuleGraphRefAll);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(563);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::GRAPH:
      case Sparql11Parser::IRI_REF:
      case Sparql11Parser::PNAME_NS:
      case Sparql11Parser::PNAME_LN: {
        enterOuterAlt(_localctx, 1);
        setState(559);
        graphRef();
        break;
      }

      case Sparql11Parser::DEFAULT: {
        enterOuterAlt(_localctx, 2);
        setState(560);
        match(Sparql11Parser::DEFAULT);
        break;
      }

      case Sparql11Parser::NAMED: {
        enterOuterAlt(_localctx, 3);
        setState(561);
        match(Sparql11Parser::NAMED);
        break;
      }

      case Sparql11Parser::ALL: {
        enterOuterAlt(_localctx, 4);
        setState(562);
        match(Sparql11Parser::ALL);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QuadPatternContext ------------------------------------------------------------------

Sparql11Parser::QuadPatternContext::QuadPatternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::QuadPatternContext::OPEN_CURLY_BRACE() {
  return getToken(Sparql11Parser::OPEN_CURLY_BRACE, 0);
}

Sparql11Parser::QuadsContext* Sparql11Parser::QuadPatternContext::quads() {
  return getRuleContext<Sparql11Parser::QuadsContext>(0);
}

tree::TerminalNode* Sparql11Parser::QuadPatternContext::CLOSE_CURLY_BRACE() {
  return getToken(Sparql11Parser::CLOSE_CURLY_BRACE, 0);
}


size_t Sparql11Parser::QuadPatternContext::getRuleIndex() const {
  return Sparql11Parser::RuleQuadPattern;
}

antlrcpp::Any Sparql11Parser::QuadPatternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitQuadPattern(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::QuadPatternContext* Sparql11Parser::quadPattern() {
  QuadPatternContext *_localctx = _tracker.createInstance<QuadPatternContext>(_ctx, getState());
  enterRule(_localctx, 88, Sparql11Parser::RuleQuadPattern);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(565);
    match(Sparql11Parser::OPEN_CURLY_BRACE);
    setState(566);
    quads();
    setState(567);
    match(Sparql11Parser::CLOSE_CURLY_BRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QuadDataContext ------------------------------------------------------------------

Sparql11Parser::QuadDataContext::QuadDataContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::QuadDataContext::OPEN_CURLY_BRACE() {
  return getToken(Sparql11Parser::OPEN_CURLY_BRACE, 0);
}

Sparql11Parser::QuadsContext* Sparql11Parser::QuadDataContext::quads() {
  return getRuleContext<Sparql11Parser::QuadsContext>(0);
}

tree::TerminalNode* Sparql11Parser::QuadDataContext::CLOSE_CURLY_BRACE() {
  return getToken(Sparql11Parser::CLOSE_CURLY_BRACE, 0);
}


size_t Sparql11Parser::QuadDataContext::getRuleIndex() const {
  return Sparql11Parser::RuleQuadData;
}

antlrcpp::Any Sparql11Parser::QuadDataContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitQuadData(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::QuadDataContext* Sparql11Parser::quadData() {
  QuadDataContext *_localctx = _tracker.createInstance<QuadDataContext>(_ctx, getState());
  enterRule(_localctx, 90, Sparql11Parser::RuleQuadData);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(569);
    match(Sparql11Parser::OPEN_CURLY_BRACE);
    setState(570);
    quads();
    setState(571);
    match(Sparql11Parser::CLOSE_CURLY_BRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QuadsContext ------------------------------------------------------------------

Sparql11Parser::QuadsContext::QuadsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Sparql11Parser::TriplesTemplateContext *> Sparql11Parser::QuadsContext::triplesTemplate() {
  return getRuleContexts<Sparql11Parser::TriplesTemplateContext>();
}

Sparql11Parser::TriplesTemplateContext* Sparql11Parser::QuadsContext::triplesTemplate(size_t i) {
  return getRuleContext<Sparql11Parser::TriplesTemplateContext>(i);
}

std::vector<Sparql11Parser::QuadsNotTriplesContext *> Sparql11Parser::QuadsContext::quadsNotTriples() {
  return getRuleContexts<Sparql11Parser::QuadsNotTriplesContext>();
}

Sparql11Parser::QuadsNotTriplesContext* Sparql11Parser::QuadsContext::quadsNotTriples(size_t i) {
  return getRuleContext<Sparql11Parser::QuadsNotTriplesContext>(i);
}

std::vector<tree::TerminalNode *> Sparql11Parser::QuadsContext::DOT() {
  return getTokens(Sparql11Parser::DOT);
}

tree::TerminalNode* Sparql11Parser::QuadsContext::DOT(size_t i) {
  return getToken(Sparql11Parser::DOT, i);
}


size_t Sparql11Parser::QuadsContext::getRuleIndex() const {
  return Sparql11Parser::RuleQuads;
}

antlrcpp::Any Sparql11Parser::QuadsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitQuads(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::QuadsContext* Sparql11Parser::quads() {
  QuadsContext *_localctx = _tracker.createInstance<QuadsContext>(_ctx, getState());
  enterRule(_localctx, 92, Sparql11Parser::RuleQuads);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(574);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 75) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 75)) & ((1ULL << (Sparql11Parser::TRUE - 75))
      | (1ULL << (Sparql11Parser::FALSE - 75))
      | (1ULL << (Sparql11Parser::IRI_REF - 75))
      | (1ULL << (Sparql11Parser::PNAME_NS - 75))
      | (1ULL << (Sparql11Parser::PNAME_LN - 75))
      | (1ULL << (Sparql11Parser::VAR1 - 75))
      | (1ULL << (Sparql11Parser::VAR2 - 75))
      | (1ULL << (Sparql11Parser::INTEGER - 75))
      | (1ULL << (Sparql11Parser::DECIMAL - 75))
      | (1ULL << (Sparql11Parser::DOUBLE - 75))
      | (1ULL << (Sparql11Parser::INTEGER_POSITIVE - 75))
      | (1ULL << (Sparql11Parser::DECIMAL_POSITIVE - 75))
      | (1ULL << (Sparql11Parser::DOUBLE_POSITIVE - 75))
      | (1ULL << (Sparql11Parser::INTEGER_NEGATIVE - 75))
      | (1ULL << (Sparql11Parser::DECIMAL_NEGATIVE - 75))
      | (1ULL << (Sparql11Parser::DOUBLE_NEGATIVE - 75))
      | (1ULL << (Sparql11Parser::STRING_LITERAL1 - 75))
      | (1ULL << (Sparql11Parser::STRING_LITERAL2 - 75))
      | (1ULL << (Sparql11Parser::STRING_LITERAL_LONG1 - 75))
      | (1ULL << (Sparql11Parser::STRING_LITERAL_LONG2 - 75))
      | (1ULL << (Sparql11Parser::BLANK_NODE_LABEL - 75))
      | (1ULL << (Sparql11Parser::OPEN_BRACE - 75))
      | (1ULL << (Sparql11Parser::OPEN_SQUARE_BRACE - 75)))) != 0)) {
      setState(573);
      triplesTemplate();
    }
    setState(585);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Sparql11Parser::GRAPH) {
      setState(576);
      quadsNotTriples();
      setState(578);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == Sparql11Parser::DOT) {
        setState(577);
        match(Sparql11Parser::DOT);
      }
      setState(581);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((((_la - 75) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 75)) & ((1ULL << (Sparql11Parser::TRUE - 75))
        | (1ULL << (Sparql11Parser::FALSE - 75))
        | (1ULL << (Sparql11Parser::IRI_REF - 75))
        | (1ULL << (Sparql11Parser::PNAME_NS - 75))
        | (1ULL << (Sparql11Parser::PNAME_LN - 75))
        | (1ULL << (Sparql11Parser::VAR1 - 75))
        | (1ULL << (Sparql11Parser::VAR2 - 75))
        | (1ULL << (Sparql11Parser::INTEGER - 75))
        | (1ULL << (Sparql11Parser::DECIMAL - 75))
        | (1ULL << (Sparql11Parser::DOUBLE - 75))
        | (1ULL << (Sparql11Parser::INTEGER_POSITIVE - 75))
        | (1ULL << (Sparql11Parser::DECIMAL_POSITIVE - 75))
        | (1ULL << (Sparql11Parser::DOUBLE_POSITIVE - 75))
        | (1ULL << (Sparql11Parser::INTEGER_NEGATIVE - 75))
        | (1ULL << (Sparql11Parser::DECIMAL_NEGATIVE - 75))
        | (1ULL << (Sparql11Parser::DOUBLE_NEGATIVE - 75))
        | (1ULL << (Sparql11Parser::STRING_LITERAL1 - 75))
        | (1ULL << (Sparql11Parser::STRING_LITERAL2 - 75))
        | (1ULL << (Sparql11Parser::STRING_LITERAL_LONG1 - 75))
        | (1ULL << (Sparql11Parser::STRING_LITERAL_LONG2 - 75))
        | (1ULL << (Sparql11Parser::BLANK_NODE_LABEL - 75))
        | (1ULL << (Sparql11Parser::OPEN_BRACE - 75))
        | (1ULL << (Sparql11Parser::OPEN_SQUARE_BRACE - 75)))) != 0)) {
        setState(580);
        triplesTemplate();
      }
      setState(587);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QuadsNotTriplesContext ------------------------------------------------------------------

Sparql11Parser::QuadsNotTriplesContext::QuadsNotTriplesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::QuadsNotTriplesContext::GRAPH() {
  return getToken(Sparql11Parser::GRAPH, 0);
}

Sparql11Parser::VarOrIriRefContext* Sparql11Parser::QuadsNotTriplesContext::varOrIriRef() {
  return getRuleContext<Sparql11Parser::VarOrIriRefContext>(0);
}

tree::TerminalNode* Sparql11Parser::QuadsNotTriplesContext::OPEN_CURLY_BRACE() {
  return getToken(Sparql11Parser::OPEN_CURLY_BRACE, 0);
}

Sparql11Parser::TriplesTemplateContext* Sparql11Parser::QuadsNotTriplesContext::triplesTemplate() {
  return getRuleContext<Sparql11Parser::TriplesTemplateContext>(0);
}

tree::TerminalNode* Sparql11Parser::QuadsNotTriplesContext::CLOSE_CURLY_BRACE() {
  return getToken(Sparql11Parser::CLOSE_CURLY_BRACE, 0);
}


size_t Sparql11Parser::QuadsNotTriplesContext::getRuleIndex() const {
  return Sparql11Parser::RuleQuadsNotTriples;
}

antlrcpp::Any Sparql11Parser::QuadsNotTriplesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitQuadsNotTriples(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::QuadsNotTriplesContext* Sparql11Parser::quadsNotTriples() {
  QuadsNotTriplesContext *_localctx = _tracker.createInstance<QuadsNotTriplesContext>(_ctx, getState());
  enterRule(_localctx, 94, Sparql11Parser::RuleQuadsNotTriples);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(588);
    match(Sparql11Parser::GRAPH);
    setState(589);
    varOrIriRef();
    setState(590);
    match(Sparql11Parser::OPEN_CURLY_BRACE);
    setState(591);
    triplesTemplate();
    setState(592);
    match(Sparql11Parser::CLOSE_CURLY_BRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TriplesTemplateContext ------------------------------------------------------------------

Sparql11Parser::TriplesTemplateContext::TriplesTemplateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::TriplesSameSubjectContext* Sparql11Parser::TriplesTemplateContext::triplesSameSubject() {
  return getRuleContext<Sparql11Parser::TriplesSameSubjectContext>(0);
}

tree::TerminalNode* Sparql11Parser::TriplesTemplateContext::DOT() {
  return getToken(Sparql11Parser::DOT, 0);
}

Sparql11Parser::TriplesTemplateContext* Sparql11Parser::TriplesTemplateContext::triplesTemplate() {
  return getRuleContext<Sparql11Parser::TriplesTemplateContext>(0);
}


size_t Sparql11Parser::TriplesTemplateContext::getRuleIndex() const {
  return Sparql11Parser::RuleTriplesTemplate;
}

antlrcpp::Any Sparql11Parser::TriplesTemplateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitTriplesTemplate(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::TriplesTemplateContext* Sparql11Parser::triplesTemplate() {
  TriplesTemplateContext *_localctx = _tracker.createInstance<TriplesTemplateContext>(_ctx, getState());
  enterRule(_localctx, 96, Sparql11Parser::RuleTriplesTemplate);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(594);
    triplesSameSubject();
    setState(599);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Sparql11Parser::DOT) {
      setState(595);
      match(Sparql11Parser::DOT);
      setState(597);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((((_la - 75) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 75)) & ((1ULL << (Sparql11Parser::TRUE - 75))
        | (1ULL << (Sparql11Parser::FALSE - 75))
        | (1ULL << (Sparql11Parser::IRI_REF - 75))
        | (1ULL << (Sparql11Parser::PNAME_NS - 75))
        | (1ULL << (Sparql11Parser::PNAME_LN - 75))
        | (1ULL << (Sparql11Parser::VAR1 - 75))
        | (1ULL << (Sparql11Parser::VAR2 - 75))
        | (1ULL << (Sparql11Parser::INTEGER - 75))
        | (1ULL << (Sparql11Parser::DECIMAL - 75))
        | (1ULL << (Sparql11Parser::DOUBLE - 75))
        | (1ULL << (Sparql11Parser::INTEGER_POSITIVE - 75))
        | (1ULL << (Sparql11Parser::DECIMAL_POSITIVE - 75))
        | (1ULL << (Sparql11Parser::DOUBLE_POSITIVE - 75))
        | (1ULL << (Sparql11Parser::INTEGER_NEGATIVE - 75))
        | (1ULL << (Sparql11Parser::DECIMAL_NEGATIVE - 75))
        | (1ULL << (Sparql11Parser::DOUBLE_NEGATIVE - 75))
        | (1ULL << (Sparql11Parser::STRING_LITERAL1 - 75))
        | (1ULL << (Sparql11Parser::STRING_LITERAL2 - 75))
        | (1ULL << (Sparql11Parser::STRING_LITERAL_LONG1 - 75))
        | (1ULL << (Sparql11Parser::STRING_LITERAL_LONG2 - 75))
        | (1ULL << (Sparql11Parser::BLANK_NODE_LABEL - 75))
        | (1ULL << (Sparql11Parser::OPEN_BRACE - 75))
        | (1ULL << (Sparql11Parser::OPEN_SQUARE_BRACE - 75)))) != 0)) {
        setState(596);
        triplesTemplate();
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GroupGraphPatternContext ------------------------------------------------------------------

Sparql11Parser::GroupGraphPatternContext::GroupGraphPatternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::GroupGraphPatternContext::OPEN_CURLY_BRACE() {
  return getToken(Sparql11Parser::OPEN_CURLY_BRACE, 0);
}

tree::TerminalNode* Sparql11Parser::GroupGraphPatternContext::CLOSE_CURLY_BRACE() {
  return getToken(Sparql11Parser::CLOSE_CURLY_BRACE, 0);
}

Sparql11Parser::SubSelectContext* Sparql11Parser::GroupGraphPatternContext::subSelect() {
  return getRuleContext<Sparql11Parser::SubSelectContext>(0);
}

Sparql11Parser::GroupGraphPatternSubContext* Sparql11Parser::GroupGraphPatternContext::groupGraphPatternSub() {
  return getRuleContext<Sparql11Parser::GroupGraphPatternSubContext>(0);
}


size_t Sparql11Parser::GroupGraphPatternContext::getRuleIndex() const {
  return Sparql11Parser::RuleGroupGraphPattern;
}

antlrcpp::Any Sparql11Parser::GroupGraphPatternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitGroupGraphPattern(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::GroupGraphPatternContext* Sparql11Parser::groupGraphPattern() {
  GroupGraphPatternContext *_localctx = _tracker.createInstance<GroupGraphPatternContext>(_ctx, getState());
  enterRule(_localctx, 98, Sparql11Parser::RuleGroupGraphPattern);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(601);
    match(Sparql11Parser::OPEN_CURLY_BRACE);
    setState(604);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::SELECT: {
        setState(602);
        subSelect();
        break;
      }

      case Sparql11Parser::SERVICE:
      case Sparql11Parser::MINUS_P:
      case Sparql11Parser::OPTIONAL:
      case Sparql11Parser::GRAPH:
      case Sparql11Parser::FILTER:
      case Sparql11Parser::TRUE:
      case Sparql11Parser::FALSE:
      case Sparql11Parser::IRI_REF:
      case Sparql11Parser::PNAME_NS:
      case Sparql11Parser::PNAME_LN:
      case Sparql11Parser::VAR1:
      case Sparql11Parser::VAR2:
      case Sparql11Parser::INTEGER:
      case Sparql11Parser::DECIMAL:
      case Sparql11Parser::DOUBLE:
      case Sparql11Parser::INTEGER_POSITIVE:
      case Sparql11Parser::DECIMAL_POSITIVE:
      case Sparql11Parser::DOUBLE_POSITIVE:
      case Sparql11Parser::INTEGER_NEGATIVE:
      case Sparql11Parser::DECIMAL_NEGATIVE:
      case Sparql11Parser::DOUBLE_NEGATIVE:
      case Sparql11Parser::STRING_LITERAL1:
      case Sparql11Parser::STRING_LITERAL2:
      case Sparql11Parser::STRING_LITERAL_LONG1:
      case Sparql11Parser::STRING_LITERAL_LONG2:
      case Sparql11Parser::BLANK_NODE_LABEL:
      case Sparql11Parser::OPEN_CURLY_BRACE:
      case Sparql11Parser::CLOSE_CURLY_BRACE:
      case Sparql11Parser::OPEN_BRACE:
      case Sparql11Parser::OPEN_SQUARE_BRACE: {
        setState(603);
        groupGraphPatternSub();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(606);
    match(Sparql11Parser::CLOSE_CURLY_BRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GroupGraphPatternSubContext ------------------------------------------------------------------

Sparql11Parser::GroupGraphPatternSubContext::GroupGraphPatternSubContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Sparql11Parser::TriplesBlockContext *> Sparql11Parser::GroupGraphPatternSubContext::triplesBlock() {
  return getRuleContexts<Sparql11Parser::TriplesBlockContext>();
}

Sparql11Parser::TriplesBlockContext* Sparql11Parser::GroupGraphPatternSubContext::triplesBlock(size_t i) {
  return getRuleContext<Sparql11Parser::TriplesBlockContext>(i);
}

std::vector<Sparql11Parser::GraphPatternNotTriplesContext *> Sparql11Parser::GroupGraphPatternSubContext::graphPatternNotTriples() {
  return getRuleContexts<Sparql11Parser::GraphPatternNotTriplesContext>();
}

Sparql11Parser::GraphPatternNotTriplesContext* Sparql11Parser::GroupGraphPatternSubContext::graphPatternNotTriples(size_t i) {
  return getRuleContext<Sparql11Parser::GraphPatternNotTriplesContext>(i);
}

std::vector<tree::TerminalNode *> Sparql11Parser::GroupGraphPatternSubContext::DOT() {
  return getTokens(Sparql11Parser::DOT);
}

tree::TerminalNode* Sparql11Parser::GroupGraphPatternSubContext::DOT(size_t i) {
  return getToken(Sparql11Parser::DOT, i);
}


size_t Sparql11Parser::GroupGraphPatternSubContext::getRuleIndex() const {
  return Sparql11Parser::RuleGroupGraphPatternSub;
}

antlrcpp::Any Sparql11Parser::GroupGraphPatternSubContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitGroupGraphPatternSub(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::GroupGraphPatternSubContext* Sparql11Parser::groupGraphPatternSub() {
  GroupGraphPatternSubContext *_localctx = _tracker.createInstance<GroupGraphPatternSubContext>(_ctx, getState());
  enterRule(_localctx, 100, Sparql11Parser::RuleGroupGraphPatternSub);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(609);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 75) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 75)) & ((1ULL << (Sparql11Parser::TRUE - 75))
      | (1ULL << (Sparql11Parser::FALSE - 75))
      | (1ULL << (Sparql11Parser::IRI_REF - 75))
      | (1ULL << (Sparql11Parser::PNAME_NS - 75))
      | (1ULL << (Sparql11Parser::PNAME_LN - 75))
      | (1ULL << (Sparql11Parser::VAR1 - 75))
      | (1ULL << (Sparql11Parser::VAR2 - 75))
      | (1ULL << (Sparql11Parser::INTEGER - 75))
      | (1ULL << (Sparql11Parser::DECIMAL - 75))
      | (1ULL << (Sparql11Parser::DOUBLE - 75))
      | (1ULL << (Sparql11Parser::INTEGER_POSITIVE - 75))
      | (1ULL << (Sparql11Parser::DECIMAL_POSITIVE - 75))
      | (1ULL << (Sparql11Parser::DOUBLE_POSITIVE - 75))
      | (1ULL << (Sparql11Parser::INTEGER_NEGATIVE - 75))
      | (1ULL << (Sparql11Parser::DECIMAL_NEGATIVE - 75))
      | (1ULL << (Sparql11Parser::DOUBLE_NEGATIVE - 75))
      | (1ULL << (Sparql11Parser::STRING_LITERAL1 - 75))
      | (1ULL << (Sparql11Parser::STRING_LITERAL2 - 75))
      | (1ULL << (Sparql11Parser::STRING_LITERAL_LONG1 - 75))
      | (1ULL << (Sparql11Parser::STRING_LITERAL_LONG2 - 75))
      | (1ULL << (Sparql11Parser::BLANK_NODE_LABEL - 75))
      | (1ULL << (Sparql11Parser::OPEN_BRACE - 75))
      | (1ULL << (Sparql11Parser::OPEN_SQUARE_BRACE - 75)))) != 0)) {
      setState(608);
      triplesBlock();
    }
    setState(620);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << Sparql11Parser::SERVICE)
      | (1ULL << Sparql11Parser::MINUS_P)
      | (1ULL << Sparql11Parser::OPTIONAL)
      | (1ULL << Sparql11Parser::GRAPH)
      | (1ULL << Sparql11Parser::FILTER))) != 0) || _la == Sparql11Parser::OPEN_CURLY_BRACE) {
      setState(611);
      graphPatternNotTriples();
      setState(613);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == Sparql11Parser::DOT) {
        setState(612);
        match(Sparql11Parser::DOT);
      }
      setState(616);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((((_la - 75) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 75)) & ((1ULL << (Sparql11Parser::TRUE - 75))
        | (1ULL << (Sparql11Parser::FALSE - 75))
        | (1ULL << (Sparql11Parser::IRI_REF - 75))
        | (1ULL << (Sparql11Parser::PNAME_NS - 75))
        | (1ULL << (Sparql11Parser::PNAME_LN - 75))
        | (1ULL << (Sparql11Parser::VAR1 - 75))
        | (1ULL << (Sparql11Parser::VAR2 - 75))
        | (1ULL << (Sparql11Parser::INTEGER - 75))
        | (1ULL << (Sparql11Parser::DECIMAL - 75))
        | (1ULL << (Sparql11Parser::DOUBLE - 75))
        | (1ULL << (Sparql11Parser::INTEGER_POSITIVE - 75))
        | (1ULL << (Sparql11Parser::DECIMAL_POSITIVE - 75))
        | (1ULL << (Sparql11Parser::DOUBLE_POSITIVE - 75))
        | (1ULL << (Sparql11Parser::INTEGER_NEGATIVE - 75))
        | (1ULL << (Sparql11Parser::DECIMAL_NEGATIVE - 75))
        | (1ULL << (Sparql11Parser::DOUBLE_NEGATIVE - 75))
        | (1ULL << (Sparql11Parser::STRING_LITERAL1 - 75))
        | (1ULL << (Sparql11Parser::STRING_LITERAL2 - 75))
        | (1ULL << (Sparql11Parser::STRING_LITERAL_LONG1 - 75))
        | (1ULL << (Sparql11Parser::STRING_LITERAL_LONG2 - 75))
        | (1ULL << (Sparql11Parser::BLANK_NODE_LABEL - 75))
        | (1ULL << (Sparql11Parser::OPEN_BRACE - 75))
        | (1ULL << (Sparql11Parser::OPEN_SQUARE_BRACE - 75)))) != 0)) {
        setState(615);
        triplesBlock();
      }
      setState(622);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TriplesBlockContext ------------------------------------------------------------------

Sparql11Parser::TriplesBlockContext::TriplesBlockContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::TriplesSameSubjectPathContext* Sparql11Parser::TriplesBlockContext::triplesSameSubjectPath() {
  return getRuleContext<Sparql11Parser::TriplesSameSubjectPathContext>(0);
}

tree::TerminalNode* Sparql11Parser::TriplesBlockContext::DOT() {
  return getToken(Sparql11Parser::DOT, 0);
}

Sparql11Parser::TriplesBlockContext* Sparql11Parser::TriplesBlockContext::triplesBlock() {
  return getRuleContext<Sparql11Parser::TriplesBlockContext>(0);
}


size_t Sparql11Parser::TriplesBlockContext::getRuleIndex() const {
  return Sparql11Parser::RuleTriplesBlock;
}

antlrcpp::Any Sparql11Parser::TriplesBlockContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitTriplesBlock(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::TriplesBlockContext* Sparql11Parser::triplesBlock() {
  TriplesBlockContext *_localctx = _tracker.createInstance<TriplesBlockContext>(_ctx, getState());
  enterRule(_localctx, 102, Sparql11Parser::RuleTriplesBlock);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(623);
    triplesSameSubjectPath();
    setState(628);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Sparql11Parser::DOT) {
      setState(624);
      match(Sparql11Parser::DOT);
      setState(626);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((((_la - 75) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 75)) & ((1ULL << (Sparql11Parser::TRUE - 75))
        | (1ULL << (Sparql11Parser::FALSE - 75))
        | (1ULL << (Sparql11Parser::IRI_REF - 75))
        | (1ULL << (Sparql11Parser::PNAME_NS - 75))
        | (1ULL << (Sparql11Parser::PNAME_LN - 75))
        | (1ULL << (Sparql11Parser::VAR1 - 75))
        | (1ULL << (Sparql11Parser::VAR2 - 75))
        | (1ULL << (Sparql11Parser::INTEGER - 75))
        | (1ULL << (Sparql11Parser::DECIMAL - 75))
        | (1ULL << (Sparql11Parser::DOUBLE - 75))
        | (1ULL << (Sparql11Parser::INTEGER_POSITIVE - 75))
        | (1ULL << (Sparql11Parser::DECIMAL_POSITIVE - 75))
        | (1ULL << (Sparql11Parser::DOUBLE_POSITIVE - 75))
        | (1ULL << (Sparql11Parser::INTEGER_NEGATIVE - 75))
        | (1ULL << (Sparql11Parser::DECIMAL_NEGATIVE - 75))
        | (1ULL << (Sparql11Parser::DOUBLE_NEGATIVE - 75))
        | (1ULL << (Sparql11Parser::STRING_LITERAL1 - 75))
        | (1ULL << (Sparql11Parser::STRING_LITERAL2 - 75))
        | (1ULL << (Sparql11Parser::STRING_LITERAL_LONG1 - 75))
        | (1ULL << (Sparql11Parser::STRING_LITERAL_LONG2 - 75))
        | (1ULL << (Sparql11Parser::BLANK_NODE_LABEL - 75))
        | (1ULL << (Sparql11Parser::OPEN_BRACE - 75))
        | (1ULL << (Sparql11Parser::OPEN_SQUARE_BRACE - 75)))) != 0)) {
        setState(625);
        triplesBlock();
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GraphPatternNotTriplesContext ------------------------------------------------------------------

Sparql11Parser::GraphPatternNotTriplesContext::GraphPatternNotTriplesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::GroupOrUnionGraphPatternContext* Sparql11Parser::GraphPatternNotTriplesContext::groupOrUnionGraphPattern() {
  return getRuleContext<Sparql11Parser::GroupOrUnionGraphPatternContext>(0);
}

Sparql11Parser::OptionalGraphPatternContext* Sparql11Parser::GraphPatternNotTriplesContext::optionalGraphPattern() {
  return getRuleContext<Sparql11Parser::OptionalGraphPatternContext>(0);
}

Sparql11Parser::MinusGraphPatternContext* Sparql11Parser::GraphPatternNotTriplesContext::minusGraphPattern() {
  return getRuleContext<Sparql11Parser::MinusGraphPatternContext>(0);
}

Sparql11Parser::GraphGraphPatternContext* Sparql11Parser::GraphPatternNotTriplesContext::graphGraphPattern() {
  return getRuleContext<Sparql11Parser::GraphGraphPatternContext>(0);
}

Sparql11Parser::ServiceGraphPatternContext* Sparql11Parser::GraphPatternNotTriplesContext::serviceGraphPattern() {
  return getRuleContext<Sparql11Parser::ServiceGraphPatternContext>(0);
}

Sparql11Parser::FilterContext* Sparql11Parser::GraphPatternNotTriplesContext::filter() {
  return getRuleContext<Sparql11Parser::FilterContext>(0);
}


size_t Sparql11Parser::GraphPatternNotTriplesContext::getRuleIndex() const {
  return Sparql11Parser::RuleGraphPatternNotTriples;
}

antlrcpp::Any Sparql11Parser::GraphPatternNotTriplesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitGraphPatternNotTriples(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::GraphPatternNotTriplesContext* Sparql11Parser::graphPatternNotTriples() {
  GraphPatternNotTriplesContext *_localctx = _tracker.createInstance<GraphPatternNotTriplesContext>(_ctx, getState());
  enterRule(_localctx, 104, Sparql11Parser::RuleGraphPatternNotTriples);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(636);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::OPEN_CURLY_BRACE: {
        enterOuterAlt(_localctx, 1);
        setState(630);
        groupOrUnionGraphPattern();
        break;
      }

      case Sparql11Parser::OPTIONAL: {
        enterOuterAlt(_localctx, 2);
        setState(631);
        optionalGraphPattern();
        break;
      }

      case Sparql11Parser::MINUS_P: {
        enterOuterAlt(_localctx, 3);
        setState(632);
        minusGraphPattern();
        break;
      }

      case Sparql11Parser::GRAPH: {
        enterOuterAlt(_localctx, 4);
        setState(633);
        graphGraphPattern();
        break;
      }

      case Sparql11Parser::SERVICE: {
        enterOuterAlt(_localctx, 5);
        setState(634);
        serviceGraphPattern();
        break;
      }

      case Sparql11Parser::FILTER: {
        enterOuterAlt(_localctx, 6);
        setState(635);
        filter();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OptionalGraphPatternContext ------------------------------------------------------------------

Sparql11Parser::OptionalGraphPatternContext::OptionalGraphPatternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::OptionalGraphPatternContext::OPTIONAL() {
  return getToken(Sparql11Parser::OPTIONAL, 0);
}

Sparql11Parser::GroupGraphPatternContext* Sparql11Parser::OptionalGraphPatternContext::groupGraphPattern() {
  return getRuleContext<Sparql11Parser::GroupGraphPatternContext>(0);
}


size_t Sparql11Parser::OptionalGraphPatternContext::getRuleIndex() const {
  return Sparql11Parser::RuleOptionalGraphPattern;
}

antlrcpp::Any Sparql11Parser::OptionalGraphPatternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitOptionalGraphPattern(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::OptionalGraphPatternContext* Sparql11Parser::optionalGraphPattern() {
  OptionalGraphPatternContext *_localctx = _tracker.createInstance<OptionalGraphPatternContext>(_ctx, getState());
  enterRule(_localctx, 106, Sparql11Parser::RuleOptionalGraphPattern);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(638);
    match(Sparql11Parser::OPTIONAL);
    setState(639);
    groupGraphPattern();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GraphGraphPatternContext ------------------------------------------------------------------

Sparql11Parser::GraphGraphPatternContext::GraphGraphPatternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::GraphGraphPatternContext::GRAPH() {
  return getToken(Sparql11Parser::GRAPH, 0);
}

Sparql11Parser::VarOrIriRefContext* Sparql11Parser::GraphGraphPatternContext::varOrIriRef() {
  return getRuleContext<Sparql11Parser::VarOrIriRefContext>(0);
}

Sparql11Parser::GroupGraphPatternContext* Sparql11Parser::GraphGraphPatternContext::groupGraphPattern() {
  return getRuleContext<Sparql11Parser::GroupGraphPatternContext>(0);
}


size_t Sparql11Parser::GraphGraphPatternContext::getRuleIndex() const {
  return Sparql11Parser::RuleGraphGraphPattern;
}

antlrcpp::Any Sparql11Parser::GraphGraphPatternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitGraphGraphPattern(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::GraphGraphPatternContext* Sparql11Parser::graphGraphPattern() {
  GraphGraphPatternContext *_localctx = _tracker.createInstance<GraphGraphPatternContext>(_ctx, getState());
  enterRule(_localctx, 108, Sparql11Parser::RuleGraphGraphPattern);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(641);
    match(Sparql11Parser::GRAPH);
    setState(642);
    varOrIriRef();
    setState(643);
    groupGraphPattern();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ServiceGraphPatternContext ------------------------------------------------------------------

Sparql11Parser::ServiceGraphPatternContext::ServiceGraphPatternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::ServiceGraphPatternContext::SERVICE() {
  return getToken(Sparql11Parser::SERVICE, 0);
}

Sparql11Parser::VarOrIriRefContext* Sparql11Parser::ServiceGraphPatternContext::varOrIriRef() {
  return getRuleContext<Sparql11Parser::VarOrIriRefContext>(0);
}

Sparql11Parser::GroupGraphPatternContext* Sparql11Parser::ServiceGraphPatternContext::groupGraphPattern() {
  return getRuleContext<Sparql11Parser::GroupGraphPatternContext>(0);
}


size_t Sparql11Parser::ServiceGraphPatternContext::getRuleIndex() const {
  return Sparql11Parser::RuleServiceGraphPattern;
}

antlrcpp::Any Sparql11Parser::ServiceGraphPatternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitServiceGraphPattern(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::ServiceGraphPatternContext* Sparql11Parser::serviceGraphPattern() {
  ServiceGraphPatternContext *_localctx = _tracker.createInstance<ServiceGraphPatternContext>(_ctx, getState());
  enterRule(_localctx, 110, Sparql11Parser::RuleServiceGraphPattern);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(645);
    match(Sparql11Parser::SERVICE);
    setState(646);
    varOrIriRef();
    setState(647);
    groupGraphPattern();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MinusGraphPatternContext ------------------------------------------------------------------

Sparql11Parser::MinusGraphPatternContext::MinusGraphPatternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::MinusGraphPatternContext::MINUS_P() {
  return getToken(Sparql11Parser::MINUS_P, 0);
}

Sparql11Parser::GroupGraphPatternContext* Sparql11Parser::MinusGraphPatternContext::groupGraphPattern() {
  return getRuleContext<Sparql11Parser::GroupGraphPatternContext>(0);
}


size_t Sparql11Parser::MinusGraphPatternContext::getRuleIndex() const {
  return Sparql11Parser::RuleMinusGraphPattern;
}

antlrcpp::Any Sparql11Parser::MinusGraphPatternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitMinusGraphPattern(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::MinusGraphPatternContext* Sparql11Parser::minusGraphPattern() {
  MinusGraphPatternContext *_localctx = _tracker.createInstance<MinusGraphPatternContext>(_ctx, getState());
  enterRule(_localctx, 112, Sparql11Parser::RuleMinusGraphPattern);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(649);
    match(Sparql11Parser::MINUS_P);
    setState(650);
    groupGraphPattern();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GroupOrUnionGraphPatternContext ------------------------------------------------------------------

Sparql11Parser::GroupOrUnionGraphPatternContext::GroupOrUnionGraphPatternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Sparql11Parser::GroupGraphPatternContext *> Sparql11Parser::GroupOrUnionGraphPatternContext::groupGraphPattern() {
  return getRuleContexts<Sparql11Parser::GroupGraphPatternContext>();
}

Sparql11Parser::GroupGraphPatternContext* Sparql11Parser::GroupOrUnionGraphPatternContext::groupGraphPattern(size_t i) {
  return getRuleContext<Sparql11Parser::GroupGraphPatternContext>(i);
}

std::vector<tree::TerminalNode *> Sparql11Parser::GroupOrUnionGraphPatternContext::UNION() {
  return getTokens(Sparql11Parser::UNION);
}

tree::TerminalNode* Sparql11Parser::GroupOrUnionGraphPatternContext::UNION(size_t i) {
  return getToken(Sparql11Parser::UNION, i);
}


size_t Sparql11Parser::GroupOrUnionGraphPatternContext::getRuleIndex() const {
  return Sparql11Parser::RuleGroupOrUnionGraphPattern;
}

antlrcpp::Any Sparql11Parser::GroupOrUnionGraphPatternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitGroupOrUnionGraphPattern(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::GroupOrUnionGraphPatternContext* Sparql11Parser::groupOrUnionGraphPattern() {
  GroupOrUnionGraphPatternContext *_localctx = _tracker.createInstance<GroupOrUnionGraphPatternContext>(_ctx, getState());
  enterRule(_localctx, 114, Sparql11Parser::RuleGroupOrUnionGraphPattern);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(652);
    groupGraphPattern();
    setState(657);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Sparql11Parser::UNION) {
      setState(653);
      match(Sparql11Parser::UNION);
      setState(654);
      groupGraphPattern();
      setState(659);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FilterContext ------------------------------------------------------------------

Sparql11Parser::FilterContext::FilterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::FilterContext::FILTER() {
  return getToken(Sparql11Parser::FILTER, 0);
}

Sparql11Parser::ConstraintContext* Sparql11Parser::FilterContext::constraint() {
  return getRuleContext<Sparql11Parser::ConstraintContext>(0);
}


size_t Sparql11Parser::FilterContext::getRuleIndex() const {
  return Sparql11Parser::RuleFilter;
}

antlrcpp::Any Sparql11Parser::FilterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitFilter(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::FilterContext* Sparql11Parser::filter() {
  FilterContext *_localctx = _tracker.createInstance<FilterContext>(_ctx, getState());
  enterRule(_localctx, 116, Sparql11Parser::RuleFilter);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(660);
    match(Sparql11Parser::FILTER);
    setState(661);
    constraint();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstraintContext ------------------------------------------------------------------

Sparql11Parser::ConstraintContext::ConstraintContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::BrackettedExpressionContext* Sparql11Parser::ConstraintContext::brackettedExpression() {
  return getRuleContext<Sparql11Parser::BrackettedExpressionContext>(0);
}

Sparql11Parser::BuiltInCallContext* Sparql11Parser::ConstraintContext::builtInCall() {
  return getRuleContext<Sparql11Parser::BuiltInCallContext>(0);
}

Sparql11Parser::FunctionCallContext* Sparql11Parser::ConstraintContext::functionCall() {
  return getRuleContext<Sparql11Parser::FunctionCallContext>(0);
}


size_t Sparql11Parser::ConstraintContext::getRuleIndex() const {
  return Sparql11Parser::RuleConstraint;
}

antlrcpp::Any Sparql11Parser::ConstraintContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitConstraint(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::ConstraintContext* Sparql11Parser::constraint() {
  ConstraintContext *_localctx = _tracker.createInstance<ConstraintContext>(_ctx, getState());
  enterRule(_localctx, 118, Sparql11Parser::RuleConstraint);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(666);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::OPEN_BRACE: {
        enterOuterAlt(_localctx, 1);
        setState(663);
        brackettedExpression();
        break;
      }

      case Sparql11Parser::EXISTS:
      case Sparql11Parser::COALESCE:
      case Sparql11Parser::IF:
      case Sparql11Parser::NOT:
      case Sparql11Parser::STR:
      case Sparql11Parser::LANG:
      case Sparql11Parser::LANGMATCHES:
      case Sparql11Parser::DATATYPE:
      case Sparql11Parser::BOUND:
      case Sparql11Parser::SAMETERM:
      case Sparql11Parser::IRI:
      case Sparql11Parser::URI:
      case Sparql11Parser::BNODE:
      case Sparql11Parser::STRLANG:
      case Sparql11Parser::STRDT:
      case Sparql11Parser::ISIRI:
      case Sparql11Parser::ISURI:
      case Sparql11Parser::ISBLANK:
      case Sparql11Parser::ISLITERAL:
      case Sparql11Parser::ISNUMERIC:
      case Sparql11Parser::REGEX: {
        enterOuterAlt(_localctx, 2);
        setState(664);
        builtInCall();
        break;
      }

      case Sparql11Parser::IRI_REF:
      case Sparql11Parser::PNAME_NS:
      case Sparql11Parser::PNAME_LN: {
        enterOuterAlt(_localctx, 3);
        setState(665);
        functionCall();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionCallContext ------------------------------------------------------------------

Sparql11Parser::FunctionCallContext::FunctionCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::IriRefContext* Sparql11Parser::FunctionCallContext::iriRef() {
  return getRuleContext<Sparql11Parser::IriRefContext>(0);
}

Sparql11Parser::ArgListContext* Sparql11Parser::FunctionCallContext::argList() {
  return getRuleContext<Sparql11Parser::ArgListContext>(0);
}


size_t Sparql11Parser::FunctionCallContext::getRuleIndex() const {
  return Sparql11Parser::RuleFunctionCall;
}

antlrcpp::Any Sparql11Parser::FunctionCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitFunctionCall(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::FunctionCallContext* Sparql11Parser::functionCall() {
  FunctionCallContext *_localctx = _tracker.createInstance<FunctionCallContext>(_ctx, getState());
  enterRule(_localctx, 120, Sparql11Parser::RuleFunctionCall);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(668);
    iriRef();
    setState(669);
    argList();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgListContext ------------------------------------------------------------------

Sparql11Parser::ArgListContext::ArgListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::ArgListContext::OPEN_BRACE() {
  return getToken(Sparql11Parser::OPEN_BRACE, 0);
}

tree::TerminalNode* Sparql11Parser::ArgListContext::CLOSE_BRACE() {
  return getToken(Sparql11Parser::CLOSE_BRACE, 0);
}

std::vector<tree::TerminalNode *> Sparql11Parser::ArgListContext::WS() {
  return getTokens(Sparql11Parser::WS);
}

tree::TerminalNode* Sparql11Parser::ArgListContext::WS(size_t i) {
  return getToken(Sparql11Parser::WS, i);
}

std::vector<Sparql11Parser::ExpressionContext *> Sparql11Parser::ArgListContext::expression() {
  return getRuleContexts<Sparql11Parser::ExpressionContext>();
}

Sparql11Parser::ExpressionContext* Sparql11Parser::ArgListContext::expression(size_t i) {
  return getRuleContext<Sparql11Parser::ExpressionContext>(i);
}

tree::TerminalNode* Sparql11Parser::ArgListContext::DISTINCT() {
  return getToken(Sparql11Parser::DISTINCT, 0);
}

std::vector<tree::TerminalNode *> Sparql11Parser::ArgListContext::COMMA() {
  return getTokens(Sparql11Parser::COMMA);
}

tree::TerminalNode* Sparql11Parser::ArgListContext::COMMA(size_t i) {
  return getToken(Sparql11Parser::COMMA, i);
}


size_t Sparql11Parser::ArgListContext::getRuleIndex() const {
  return Sparql11Parser::RuleArgList;
}

antlrcpp::Any Sparql11Parser::ArgListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitArgList(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::ArgListContext* Sparql11Parser::argList() {
  ArgListContext *_localctx = _tracker.createInstance<ArgListContext>(_ctx, getState());
  enterRule(_localctx, 122, Sparql11Parser::RuleArgList);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(693);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 69, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(671);
      match(Sparql11Parser::OPEN_BRACE);
      setState(675);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == Sparql11Parser::WS) {
        setState(672);
        match(Sparql11Parser::WS);
        setState(677);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(678);
      match(Sparql11Parser::CLOSE_BRACE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(679);
      match(Sparql11Parser::OPEN_BRACE);
      setState(681);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == Sparql11Parser::DISTINCT) {
        setState(680);
        match(Sparql11Parser::DISTINCT);
      }
      setState(683);
      expression();
      setState(688);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == Sparql11Parser::COMMA) {
        setState(684);
        match(Sparql11Parser::COMMA);
        setState(685);
        expression();
        setState(690);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(691);
      match(Sparql11Parser::CLOSE_BRACE);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionListContext ------------------------------------------------------------------

Sparql11Parser::ExpressionListContext::ExpressionListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::ExpressionListContext::OPEN_BRACE() {
  return getToken(Sparql11Parser::OPEN_BRACE, 0);
}

tree::TerminalNode* Sparql11Parser::ExpressionListContext::CLOSE_BRACE() {
  return getToken(Sparql11Parser::CLOSE_BRACE, 0);
}

std::vector<tree::TerminalNode *> Sparql11Parser::ExpressionListContext::WS() {
  return getTokens(Sparql11Parser::WS);
}

tree::TerminalNode* Sparql11Parser::ExpressionListContext::WS(size_t i) {
  return getToken(Sparql11Parser::WS, i);
}

std::vector<Sparql11Parser::ExpressionContext *> Sparql11Parser::ExpressionListContext::expression() {
  return getRuleContexts<Sparql11Parser::ExpressionContext>();
}

Sparql11Parser::ExpressionContext* Sparql11Parser::ExpressionListContext::expression(size_t i) {
  return getRuleContext<Sparql11Parser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> Sparql11Parser::ExpressionListContext::COMMA() {
  return getTokens(Sparql11Parser::COMMA);
}

tree::TerminalNode* Sparql11Parser::ExpressionListContext::COMMA(size_t i) {
  return getToken(Sparql11Parser::COMMA, i);
}


size_t Sparql11Parser::ExpressionListContext::getRuleIndex() const {
  return Sparql11Parser::RuleExpressionList;
}

antlrcpp::Any Sparql11Parser::ExpressionListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitExpressionList(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::ExpressionListContext* Sparql11Parser::expressionList() {
  ExpressionListContext *_localctx = _tracker.createInstance<ExpressionListContext>(_ctx, getState());
  enterRule(_localctx, 124, Sparql11Parser::RuleExpressionList);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(714);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 72, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(695);
      match(Sparql11Parser::OPEN_BRACE);
      setState(699);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == Sparql11Parser::WS) {
        setState(696);
        match(Sparql11Parser::WS);
        setState(701);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(702);
      match(Sparql11Parser::CLOSE_BRACE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(703);
      match(Sparql11Parser::OPEN_BRACE);
      setState(704);
      expression();
      setState(709);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == Sparql11Parser::COMMA) {
        setState(705);
        match(Sparql11Parser::COMMA);
        setState(706);
        expression();
        setState(711);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(712);
      match(Sparql11Parser::CLOSE_BRACE);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstructTemplateContext ------------------------------------------------------------------

Sparql11Parser::ConstructTemplateContext::ConstructTemplateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::ConstructTemplateContext::OPEN_CURLY_BRACE() {
  return getToken(Sparql11Parser::OPEN_CURLY_BRACE, 0);
}

tree::TerminalNode* Sparql11Parser::ConstructTemplateContext::CLOSE_CURLY_BRACE() {
  return getToken(Sparql11Parser::CLOSE_CURLY_BRACE, 0);
}

Sparql11Parser::ConstructTriplesContext* Sparql11Parser::ConstructTemplateContext::constructTriples() {
  return getRuleContext<Sparql11Parser::ConstructTriplesContext>(0);
}


size_t Sparql11Parser::ConstructTemplateContext::getRuleIndex() const {
  return Sparql11Parser::RuleConstructTemplate;
}

antlrcpp::Any Sparql11Parser::ConstructTemplateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitConstructTemplate(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::ConstructTemplateContext* Sparql11Parser::constructTemplate() {
  ConstructTemplateContext *_localctx = _tracker.createInstance<ConstructTemplateContext>(_ctx, getState());
  enterRule(_localctx, 126, Sparql11Parser::RuleConstructTemplate);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(716);
    match(Sparql11Parser::OPEN_CURLY_BRACE);
    setState(718);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 75) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 75)) & ((1ULL << (Sparql11Parser::TRUE - 75))
      | (1ULL << (Sparql11Parser::FALSE - 75))
      | (1ULL << (Sparql11Parser::IRI_REF - 75))
      | (1ULL << (Sparql11Parser::PNAME_NS - 75))
      | (1ULL << (Sparql11Parser::PNAME_LN - 75))
      | (1ULL << (Sparql11Parser::VAR1 - 75))
      | (1ULL << (Sparql11Parser::VAR2 - 75))
      | (1ULL << (Sparql11Parser::INTEGER - 75))
      | (1ULL << (Sparql11Parser::DECIMAL - 75))
      | (1ULL << (Sparql11Parser::DOUBLE - 75))
      | (1ULL << (Sparql11Parser::INTEGER_POSITIVE - 75))
      | (1ULL << (Sparql11Parser::DECIMAL_POSITIVE - 75))
      | (1ULL << (Sparql11Parser::DOUBLE_POSITIVE - 75))
      | (1ULL << (Sparql11Parser::INTEGER_NEGATIVE - 75))
      | (1ULL << (Sparql11Parser::DECIMAL_NEGATIVE - 75))
      | (1ULL << (Sparql11Parser::DOUBLE_NEGATIVE - 75))
      | (1ULL << (Sparql11Parser::STRING_LITERAL1 - 75))
      | (1ULL << (Sparql11Parser::STRING_LITERAL2 - 75))
      | (1ULL << (Sparql11Parser::STRING_LITERAL_LONG1 - 75))
      | (1ULL << (Sparql11Parser::STRING_LITERAL_LONG2 - 75))
      | (1ULL << (Sparql11Parser::BLANK_NODE_LABEL - 75))
      | (1ULL << (Sparql11Parser::OPEN_BRACE - 75))
      | (1ULL << (Sparql11Parser::OPEN_SQUARE_BRACE - 75)))) != 0)) {
      setState(717);
      constructTriples();
    }
    setState(720);
    match(Sparql11Parser::CLOSE_CURLY_BRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstructTriplesContext ------------------------------------------------------------------

Sparql11Parser::ConstructTriplesContext::ConstructTriplesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::TriplesSameSubjectContext* Sparql11Parser::ConstructTriplesContext::triplesSameSubject() {
  return getRuleContext<Sparql11Parser::TriplesSameSubjectContext>(0);
}

tree::TerminalNode* Sparql11Parser::ConstructTriplesContext::DOT() {
  return getToken(Sparql11Parser::DOT, 0);
}

Sparql11Parser::ConstructTriplesContext* Sparql11Parser::ConstructTriplesContext::constructTriples() {
  return getRuleContext<Sparql11Parser::ConstructTriplesContext>(0);
}


size_t Sparql11Parser::ConstructTriplesContext::getRuleIndex() const {
  return Sparql11Parser::RuleConstructTriples;
}

antlrcpp::Any Sparql11Parser::ConstructTriplesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitConstructTriples(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::ConstructTriplesContext* Sparql11Parser::constructTriples() {
  ConstructTriplesContext *_localctx = _tracker.createInstance<ConstructTriplesContext>(_ctx, getState());
  enterRule(_localctx, 128, Sparql11Parser::RuleConstructTriples);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(722);
    triplesSameSubject();
    setState(727);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Sparql11Parser::DOT) {
      setState(723);
      match(Sparql11Parser::DOT);
      setState(725);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((((_la - 75) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 75)) & ((1ULL << (Sparql11Parser::TRUE - 75))
        | (1ULL << (Sparql11Parser::FALSE - 75))
        | (1ULL << (Sparql11Parser::IRI_REF - 75))
        | (1ULL << (Sparql11Parser::PNAME_NS - 75))
        | (1ULL << (Sparql11Parser::PNAME_LN - 75))
        | (1ULL << (Sparql11Parser::VAR1 - 75))
        | (1ULL << (Sparql11Parser::VAR2 - 75))
        | (1ULL << (Sparql11Parser::INTEGER - 75))
        | (1ULL << (Sparql11Parser::DECIMAL - 75))
        | (1ULL << (Sparql11Parser::DOUBLE - 75))
        | (1ULL << (Sparql11Parser::INTEGER_POSITIVE - 75))
        | (1ULL << (Sparql11Parser::DECIMAL_POSITIVE - 75))
        | (1ULL << (Sparql11Parser::DOUBLE_POSITIVE - 75))
        | (1ULL << (Sparql11Parser::INTEGER_NEGATIVE - 75))
        | (1ULL << (Sparql11Parser::DECIMAL_NEGATIVE - 75))
        | (1ULL << (Sparql11Parser::DOUBLE_NEGATIVE - 75))
        | (1ULL << (Sparql11Parser::STRING_LITERAL1 - 75))
        | (1ULL << (Sparql11Parser::STRING_LITERAL2 - 75))
        | (1ULL << (Sparql11Parser::STRING_LITERAL_LONG1 - 75))
        | (1ULL << (Sparql11Parser::STRING_LITERAL_LONG2 - 75))
        | (1ULL << (Sparql11Parser::BLANK_NODE_LABEL - 75))
        | (1ULL << (Sparql11Parser::OPEN_BRACE - 75))
        | (1ULL << (Sparql11Parser::OPEN_SQUARE_BRACE - 75)))) != 0)) {
        setState(724);
        constructTriples();
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TriplesSameSubjectContext ------------------------------------------------------------------

Sparql11Parser::TriplesSameSubjectContext::TriplesSameSubjectContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::VarOrTermContext* Sparql11Parser::TriplesSameSubjectContext::varOrTerm() {
  return getRuleContext<Sparql11Parser::VarOrTermContext>(0);
}

Sparql11Parser::PropertyListNotEmptyContext* Sparql11Parser::TriplesSameSubjectContext::propertyListNotEmpty() {
  return getRuleContext<Sparql11Parser::PropertyListNotEmptyContext>(0);
}

Sparql11Parser::TriplesNodeContext* Sparql11Parser::TriplesSameSubjectContext::triplesNode() {
  return getRuleContext<Sparql11Parser::TriplesNodeContext>(0);
}

Sparql11Parser::PropertyListContext* Sparql11Parser::TriplesSameSubjectContext::propertyList() {
  return getRuleContext<Sparql11Parser::PropertyListContext>(0);
}


size_t Sparql11Parser::TriplesSameSubjectContext::getRuleIndex() const {
  return Sparql11Parser::RuleTriplesSameSubject;
}

antlrcpp::Any Sparql11Parser::TriplesSameSubjectContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitTriplesSameSubject(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::TriplesSameSubjectContext* Sparql11Parser::triplesSameSubject() {
  TriplesSameSubjectContext *_localctx = _tracker.createInstance<TriplesSameSubjectContext>(_ctx, getState());
  enterRule(_localctx, 130, Sparql11Parser::RuleTriplesSameSubject);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(735);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 76, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(729);
      varOrTerm();
      setState(730);
      propertyListNotEmpty();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(732);
      triplesNode();
      setState(733);
      propertyList();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PropertyListNotEmptyContext ------------------------------------------------------------------

Sparql11Parser::PropertyListNotEmptyContext::PropertyListNotEmptyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Sparql11Parser::VerbContext *> Sparql11Parser::PropertyListNotEmptyContext::verb() {
  return getRuleContexts<Sparql11Parser::VerbContext>();
}

Sparql11Parser::VerbContext* Sparql11Parser::PropertyListNotEmptyContext::verb(size_t i) {
  return getRuleContext<Sparql11Parser::VerbContext>(i);
}

std::vector<Sparql11Parser::ObjectListContext *> Sparql11Parser::PropertyListNotEmptyContext::objectList() {
  return getRuleContexts<Sparql11Parser::ObjectListContext>();
}

Sparql11Parser::ObjectListContext* Sparql11Parser::PropertyListNotEmptyContext::objectList(size_t i) {
  return getRuleContext<Sparql11Parser::ObjectListContext>(i);
}

std::vector<tree::TerminalNode *> Sparql11Parser::PropertyListNotEmptyContext::SEMICOLON() {
  return getTokens(Sparql11Parser::SEMICOLON);
}

tree::TerminalNode* Sparql11Parser::PropertyListNotEmptyContext::SEMICOLON(size_t i) {
  return getToken(Sparql11Parser::SEMICOLON, i);
}


size_t Sparql11Parser::PropertyListNotEmptyContext::getRuleIndex() const {
  return Sparql11Parser::RulePropertyListNotEmpty;
}

antlrcpp::Any Sparql11Parser::PropertyListNotEmptyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitPropertyListNotEmpty(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::PropertyListNotEmptyContext* Sparql11Parser::propertyListNotEmpty() {
  PropertyListNotEmptyContext *_localctx = _tracker.createInstance<PropertyListNotEmptyContext>(_ctx, getState());
  enterRule(_localctx, 132, Sparql11Parser::RulePropertyListNotEmpty);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(737);
    verb();
    setState(738);
    objectList();
    setState(747);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Sparql11Parser::SEMICOLON) {
      setState(739);
      match(Sparql11Parser::SEMICOLON);
      setState(743);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((((_la - 56) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 56)) & ((1ULL << (Sparql11Parser::A - 56))
        | (1ULL << (Sparql11Parser::IRI_REF - 56))
        | (1ULL << (Sparql11Parser::PNAME_NS - 56))
        | (1ULL << (Sparql11Parser::PNAME_LN - 56))
        | (1ULL << (Sparql11Parser::VAR1 - 56))
        | (1ULL << (Sparql11Parser::VAR2 - 56)))) != 0)) {
        setState(740);
        verb();
        setState(741);
        objectList();
      }
      setState(749);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PropertyListContext ------------------------------------------------------------------

Sparql11Parser::PropertyListContext::PropertyListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::PropertyListNotEmptyContext* Sparql11Parser::PropertyListContext::propertyListNotEmpty() {
  return getRuleContext<Sparql11Parser::PropertyListNotEmptyContext>(0);
}


size_t Sparql11Parser::PropertyListContext::getRuleIndex() const {
  return Sparql11Parser::RulePropertyList;
}

antlrcpp::Any Sparql11Parser::PropertyListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitPropertyList(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::PropertyListContext* Sparql11Parser::propertyList() {
  PropertyListContext *_localctx = _tracker.createInstance<PropertyListContext>(_ctx, getState());
  enterRule(_localctx, 134, Sparql11Parser::RulePropertyList);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(751);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 56) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 56)) & ((1ULL << (Sparql11Parser::A - 56))
      | (1ULL << (Sparql11Parser::IRI_REF - 56))
      | (1ULL << (Sparql11Parser::PNAME_NS - 56))
      | (1ULL << (Sparql11Parser::PNAME_LN - 56))
      | (1ULL << (Sparql11Parser::VAR1 - 56))
      | (1ULL << (Sparql11Parser::VAR2 - 56)))) != 0)) {
      setState(750);
      propertyListNotEmpty();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ObjectListContext ------------------------------------------------------------------

Sparql11Parser::ObjectListContext::ObjectListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Sparql11Parser::ObjectContext *> Sparql11Parser::ObjectListContext::object() {
  return getRuleContexts<Sparql11Parser::ObjectContext>();
}

Sparql11Parser::ObjectContext* Sparql11Parser::ObjectListContext::object(size_t i) {
  return getRuleContext<Sparql11Parser::ObjectContext>(i);
}

std::vector<tree::TerminalNode *> Sparql11Parser::ObjectListContext::COMMA() {
  return getTokens(Sparql11Parser::COMMA);
}

tree::TerminalNode* Sparql11Parser::ObjectListContext::COMMA(size_t i) {
  return getToken(Sparql11Parser::COMMA, i);
}


size_t Sparql11Parser::ObjectListContext::getRuleIndex() const {
  return Sparql11Parser::RuleObjectList;
}

antlrcpp::Any Sparql11Parser::ObjectListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitObjectList(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::ObjectListContext* Sparql11Parser::objectList() {
  ObjectListContext *_localctx = _tracker.createInstance<ObjectListContext>(_ctx, getState());
  enterRule(_localctx, 136, Sparql11Parser::RuleObjectList);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(753);
    object();
    setState(758);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Sparql11Parser::COMMA) {
      setState(754);
      match(Sparql11Parser::COMMA);
      setState(755);
      object();
      setState(760);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ObjectContext ------------------------------------------------------------------

Sparql11Parser::ObjectContext::ObjectContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::GraphNodeContext* Sparql11Parser::ObjectContext::graphNode() {
  return getRuleContext<Sparql11Parser::GraphNodeContext>(0);
}


size_t Sparql11Parser::ObjectContext::getRuleIndex() const {
  return Sparql11Parser::RuleObject;
}

antlrcpp::Any Sparql11Parser::ObjectContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitObject(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::ObjectContext* Sparql11Parser::object() {
  ObjectContext *_localctx = _tracker.createInstance<ObjectContext>(_ctx, getState());
  enterRule(_localctx, 138, Sparql11Parser::RuleObject);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(761);
    graphNode();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VerbContext ------------------------------------------------------------------

Sparql11Parser::VerbContext::VerbContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::VarOrIriRefContext* Sparql11Parser::VerbContext::varOrIriRef() {
  return getRuleContext<Sparql11Parser::VarOrIriRefContext>(0);
}

tree::TerminalNode* Sparql11Parser::VerbContext::A() {
  return getToken(Sparql11Parser::A, 0);
}


size_t Sparql11Parser::VerbContext::getRuleIndex() const {
  return Sparql11Parser::RuleVerb;
}

antlrcpp::Any Sparql11Parser::VerbContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitVerb(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::VerbContext* Sparql11Parser::verb() {
  VerbContext *_localctx = _tracker.createInstance<VerbContext>(_ctx, getState());
  enterRule(_localctx, 140, Sparql11Parser::RuleVerb);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(765);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::IRI_REF:
      case Sparql11Parser::PNAME_NS:
      case Sparql11Parser::PNAME_LN:
      case Sparql11Parser::VAR1:
      case Sparql11Parser::VAR2: {
        enterOuterAlt(_localctx, 1);
        setState(763);
        varOrIriRef();
        break;
      }

      case Sparql11Parser::A: {
        enterOuterAlt(_localctx, 2);
        setState(764);
        match(Sparql11Parser::A);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TriplesSameSubjectPathContext ------------------------------------------------------------------

Sparql11Parser::TriplesSameSubjectPathContext::TriplesSameSubjectPathContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::VarOrTermContext* Sparql11Parser::TriplesSameSubjectPathContext::varOrTerm() {
  return getRuleContext<Sparql11Parser::VarOrTermContext>(0);
}

Sparql11Parser::PropertyListNotEmptyPathContext* Sparql11Parser::TriplesSameSubjectPathContext::propertyListNotEmptyPath() {
  return getRuleContext<Sparql11Parser::PropertyListNotEmptyPathContext>(0);
}

Sparql11Parser::TriplesNodeContext* Sparql11Parser::TriplesSameSubjectPathContext::triplesNode() {
  return getRuleContext<Sparql11Parser::TriplesNodeContext>(0);
}

Sparql11Parser::PropertyListPathContext* Sparql11Parser::TriplesSameSubjectPathContext::propertyListPath() {
  return getRuleContext<Sparql11Parser::PropertyListPathContext>(0);
}


size_t Sparql11Parser::TriplesSameSubjectPathContext::getRuleIndex() const {
  return Sparql11Parser::RuleTriplesSameSubjectPath;
}

antlrcpp::Any Sparql11Parser::TriplesSameSubjectPathContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitTriplesSameSubjectPath(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::TriplesSameSubjectPathContext* Sparql11Parser::triplesSameSubjectPath() {
  TriplesSameSubjectPathContext *_localctx = _tracker.createInstance<TriplesSameSubjectPathContext>(_ctx, getState());
  enterRule(_localctx, 142, Sparql11Parser::RuleTriplesSameSubjectPath);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(773);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 82, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(767);
      varOrTerm();
      setState(768);
      propertyListNotEmptyPath();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(770);
      triplesNode();
      setState(771);
      propertyListPath();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PropertyListNotEmptyPathContext ------------------------------------------------------------------

Sparql11Parser::PropertyListNotEmptyPathContext::PropertyListNotEmptyPathContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Sparql11Parser::ObjectListContext *> Sparql11Parser::PropertyListNotEmptyPathContext::objectList() {
  return getRuleContexts<Sparql11Parser::ObjectListContext>();
}

Sparql11Parser::ObjectListContext* Sparql11Parser::PropertyListNotEmptyPathContext::objectList(size_t i) {
  return getRuleContext<Sparql11Parser::ObjectListContext>(i);
}

std::vector<Sparql11Parser::VerbPathContext *> Sparql11Parser::PropertyListNotEmptyPathContext::verbPath() {
  return getRuleContexts<Sparql11Parser::VerbPathContext>();
}

Sparql11Parser::VerbPathContext* Sparql11Parser::PropertyListNotEmptyPathContext::verbPath(size_t i) {
  return getRuleContext<Sparql11Parser::VerbPathContext>(i);
}

std::vector<Sparql11Parser::VerbSimpleContext *> Sparql11Parser::PropertyListNotEmptyPathContext::verbSimple() {
  return getRuleContexts<Sparql11Parser::VerbSimpleContext>();
}

Sparql11Parser::VerbSimpleContext* Sparql11Parser::PropertyListNotEmptyPathContext::verbSimple(size_t i) {
  return getRuleContext<Sparql11Parser::VerbSimpleContext>(i);
}

std::vector<tree::TerminalNode *> Sparql11Parser::PropertyListNotEmptyPathContext::SEMICOLON() {
  return getTokens(Sparql11Parser::SEMICOLON);
}

tree::TerminalNode* Sparql11Parser::PropertyListNotEmptyPathContext::SEMICOLON(size_t i) {
  return getToken(Sparql11Parser::SEMICOLON, i);
}


size_t Sparql11Parser::PropertyListNotEmptyPathContext::getRuleIndex() const {
  return Sparql11Parser::RulePropertyListNotEmptyPath;
}

antlrcpp::Any Sparql11Parser::PropertyListNotEmptyPathContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitPropertyListNotEmptyPath(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::PropertyListNotEmptyPathContext* Sparql11Parser::propertyListNotEmptyPath() {
  PropertyListNotEmptyPathContext *_localctx = _tracker.createInstance<PropertyListNotEmptyPathContext>(_ctx, getState());
  enterRule(_localctx, 144, Sparql11Parser::RulePropertyListNotEmptyPath);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(777);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::A:
      case Sparql11Parser::IRI_REF:
      case Sparql11Parser::PNAME_NS:
      case Sparql11Parser::PNAME_LN:
      case Sparql11Parser::NOT_SIGN:
      case Sparql11Parser::OPEN_BRACE:
      case Sparql11Parser::HAT_LABEL: {
        setState(775);
        verbPath();
        break;
      }

      case Sparql11Parser::VAR1:
      case Sparql11Parser::VAR2: {
        setState(776);
        verbSimple();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(779);
    objectList();
    setState(791);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Sparql11Parser::SEMICOLON) {
      setState(780);
      match(Sparql11Parser::SEMICOLON);
      setState(787);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == Sparql11Parser::A || ((((_la - 77) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 77)) & ((1ULL << (Sparql11Parser::IRI_REF - 77))
        | (1ULL << (Sparql11Parser::PNAME_NS - 77))
        | (1ULL << (Sparql11Parser::PNAME_LN - 77))
        | (1ULL << (Sparql11Parser::VAR1 - 77))
        | (1ULL << (Sparql11Parser::VAR2 - 77))
        | (1ULL << (Sparql11Parser::NOT_SIGN - 77))
        | (1ULL << (Sparql11Parser::OPEN_BRACE - 77))
        | (1ULL << (Sparql11Parser::HAT_LABEL - 77)))) != 0)) {
        setState(783);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case Sparql11Parser::A:
          case Sparql11Parser::IRI_REF:
          case Sparql11Parser::PNAME_NS:
          case Sparql11Parser::PNAME_LN:
          case Sparql11Parser::NOT_SIGN:
          case Sparql11Parser::OPEN_BRACE:
          case Sparql11Parser::HAT_LABEL: {
            setState(781);
            verbPath();
            break;
          }

          case Sparql11Parser::VAR1:
          case Sparql11Parser::VAR2: {
            setState(782);
            verbSimple();
            break;
          }

        default:
          throw NoViableAltException(this);
        }
        setState(785);
        objectList();
      }
      setState(793);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PropertyListPathContext ------------------------------------------------------------------

Sparql11Parser::PropertyListPathContext::PropertyListPathContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::PropertyListNotEmptyContext* Sparql11Parser::PropertyListPathContext::propertyListNotEmpty() {
  return getRuleContext<Sparql11Parser::PropertyListNotEmptyContext>(0);
}


size_t Sparql11Parser::PropertyListPathContext::getRuleIndex() const {
  return Sparql11Parser::RulePropertyListPath;
}

antlrcpp::Any Sparql11Parser::PropertyListPathContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitPropertyListPath(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::PropertyListPathContext* Sparql11Parser::propertyListPath() {
  PropertyListPathContext *_localctx = _tracker.createInstance<PropertyListPathContext>(_ctx, getState());
  enterRule(_localctx, 146, Sparql11Parser::RulePropertyListPath);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(795);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 56) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 56)) & ((1ULL << (Sparql11Parser::A - 56))
      | (1ULL << (Sparql11Parser::IRI_REF - 56))
      | (1ULL << (Sparql11Parser::PNAME_NS - 56))
      | (1ULL << (Sparql11Parser::PNAME_LN - 56))
      | (1ULL << (Sparql11Parser::VAR1 - 56))
      | (1ULL << (Sparql11Parser::VAR2 - 56)))) != 0)) {
      setState(794);
      propertyListNotEmpty();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VerbPathContext ------------------------------------------------------------------

Sparql11Parser::VerbPathContext::VerbPathContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::PathContext* Sparql11Parser::VerbPathContext::path() {
  return getRuleContext<Sparql11Parser::PathContext>(0);
}


size_t Sparql11Parser::VerbPathContext::getRuleIndex() const {
  return Sparql11Parser::RuleVerbPath;
}

antlrcpp::Any Sparql11Parser::VerbPathContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitVerbPath(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::VerbPathContext* Sparql11Parser::verbPath() {
  VerbPathContext *_localctx = _tracker.createInstance<VerbPathContext>(_ctx, getState());
  enterRule(_localctx, 148, Sparql11Parser::RuleVerbPath);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(797);
    path();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VerbSimpleContext ------------------------------------------------------------------

Sparql11Parser::VerbSimpleContext::VerbSimpleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::VariableContext* Sparql11Parser::VerbSimpleContext::variable() {
  return getRuleContext<Sparql11Parser::VariableContext>(0);
}


size_t Sparql11Parser::VerbSimpleContext::getRuleIndex() const {
  return Sparql11Parser::RuleVerbSimple;
}

antlrcpp::Any Sparql11Parser::VerbSimpleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitVerbSimple(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::VerbSimpleContext* Sparql11Parser::verbSimple() {
  VerbSimpleContext *_localctx = _tracker.createInstance<VerbSimpleContext>(_ctx, getState());
  enterRule(_localctx, 150, Sparql11Parser::RuleVerbSimple);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(799);
    variable();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PathContext ------------------------------------------------------------------

Sparql11Parser::PathContext::PathContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::PathAlternativeContext* Sparql11Parser::PathContext::pathAlternative() {
  return getRuleContext<Sparql11Parser::PathAlternativeContext>(0);
}


size_t Sparql11Parser::PathContext::getRuleIndex() const {
  return Sparql11Parser::RulePath;
}

antlrcpp::Any Sparql11Parser::PathContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitPath(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::PathContext* Sparql11Parser::path() {
  PathContext *_localctx = _tracker.createInstance<PathContext>(_ctx, getState());
  enterRule(_localctx, 152, Sparql11Parser::RulePath);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(801);
    pathAlternative();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PathAlternativeContext ------------------------------------------------------------------

Sparql11Parser::PathAlternativeContext::PathAlternativeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Sparql11Parser::PathSequenceContext *> Sparql11Parser::PathAlternativeContext::pathSequence() {
  return getRuleContexts<Sparql11Parser::PathSequenceContext>();
}

Sparql11Parser::PathSequenceContext* Sparql11Parser::PathAlternativeContext::pathSequence(size_t i) {
  return getRuleContext<Sparql11Parser::PathSequenceContext>(i);
}

std::vector<tree::TerminalNode *> Sparql11Parser::PathAlternativeContext::PIPE() {
  return getTokens(Sparql11Parser::PIPE);
}

tree::TerminalNode* Sparql11Parser::PathAlternativeContext::PIPE(size_t i) {
  return getToken(Sparql11Parser::PIPE, i);
}


size_t Sparql11Parser::PathAlternativeContext::getRuleIndex() const {
  return Sparql11Parser::RulePathAlternative;
}

antlrcpp::Any Sparql11Parser::PathAlternativeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitPathAlternative(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::PathAlternativeContext* Sparql11Parser::pathAlternative() {
  PathAlternativeContext *_localctx = _tracker.createInstance<PathAlternativeContext>(_ctx, getState());
  enterRule(_localctx, 154, Sparql11Parser::RulePathAlternative);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(803);
    pathSequence();
    setState(808);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Sparql11Parser::PIPE) {
      setState(804);
      match(Sparql11Parser::PIPE);
      setState(805);
      pathSequence();
      setState(810);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PathSequenceContext ------------------------------------------------------------------

Sparql11Parser::PathSequenceContext::PathSequenceContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Sparql11Parser::PathEltOrInverseContext *> Sparql11Parser::PathSequenceContext::pathEltOrInverse() {
  return getRuleContexts<Sparql11Parser::PathEltOrInverseContext>();
}

Sparql11Parser::PathEltOrInverseContext* Sparql11Parser::PathSequenceContext::pathEltOrInverse(size_t i) {
  return getRuleContext<Sparql11Parser::PathEltOrInverseContext>(i);
}

std::vector<tree::TerminalNode *> Sparql11Parser::PathSequenceContext::DIVIDE() {
  return getTokens(Sparql11Parser::DIVIDE);
}

tree::TerminalNode* Sparql11Parser::PathSequenceContext::DIVIDE(size_t i) {
  return getToken(Sparql11Parser::DIVIDE, i);
}


size_t Sparql11Parser::PathSequenceContext::getRuleIndex() const {
  return Sparql11Parser::RulePathSequence;
}

antlrcpp::Any Sparql11Parser::PathSequenceContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitPathSequence(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::PathSequenceContext* Sparql11Parser::pathSequence() {
  PathSequenceContext *_localctx = _tracker.createInstance<PathSequenceContext>(_ctx, getState());
  enterRule(_localctx, 156, Sparql11Parser::RulePathSequence);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(811);
    pathEltOrInverse();
    setState(816);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Sparql11Parser::DIVIDE) {
      setState(812);
      match(Sparql11Parser::DIVIDE);
      setState(813);
      pathEltOrInverse();
      setState(818);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PathEltContext ------------------------------------------------------------------

Sparql11Parser::PathEltContext::PathEltContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::PathPrimaryContext* Sparql11Parser::PathEltContext::pathPrimary() {
  return getRuleContext<Sparql11Parser::PathPrimaryContext>(0);
}

Sparql11Parser::PathModContext* Sparql11Parser::PathEltContext::pathMod() {
  return getRuleContext<Sparql11Parser::PathModContext>(0);
}


size_t Sparql11Parser::PathEltContext::getRuleIndex() const {
  return Sparql11Parser::RulePathElt;
}

antlrcpp::Any Sparql11Parser::PathEltContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitPathElt(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::PathEltContext* Sparql11Parser::pathElt() {
  PathEltContext *_localctx = _tracker.createInstance<PathEltContext>(_ctx, getState());
  enterRule(_localctx, 158, Sparql11Parser::RulePathElt);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(819);
    pathPrimary();
    setState(821);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 103) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 103)) & ((1ULL << (Sparql11Parser::OPEN_CURLY_BRACE - 103))
      | (1ULL << (Sparql11Parser::PLUS - 103))
      | (1ULL << (Sparql11Parser::ASTERISK - 103))
      | (1ULL << (Sparql11Parser::QUESTION_MARK_LABEL - 103)))) != 0)) {
      setState(820);
      pathMod();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PathEltOrInverseContext ------------------------------------------------------------------

Sparql11Parser::PathEltOrInverseContext::PathEltOrInverseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::PathEltContext* Sparql11Parser::PathEltOrInverseContext::pathElt() {
  return getRuleContext<Sparql11Parser::PathEltContext>(0);
}

tree::TerminalNode* Sparql11Parser::PathEltOrInverseContext::HAT_LABEL() {
  return getToken(Sparql11Parser::HAT_LABEL, 0);
}


size_t Sparql11Parser::PathEltOrInverseContext::getRuleIndex() const {
  return Sparql11Parser::RulePathEltOrInverse;
}

antlrcpp::Any Sparql11Parser::PathEltOrInverseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitPathEltOrInverse(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::PathEltOrInverseContext* Sparql11Parser::pathEltOrInverse() {
  PathEltOrInverseContext *_localctx = _tracker.createInstance<PathEltOrInverseContext>(_ctx, getState());
  enterRule(_localctx, 160, Sparql11Parser::RulePathEltOrInverse);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(826);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::A:
      case Sparql11Parser::IRI_REF:
      case Sparql11Parser::PNAME_NS:
      case Sparql11Parser::PNAME_LN:
      case Sparql11Parser::NOT_SIGN:
      case Sparql11Parser::OPEN_BRACE: {
        enterOuterAlt(_localctx, 1);
        setState(823);
        pathElt();
        break;
      }

      case Sparql11Parser::HAT_LABEL: {
        enterOuterAlt(_localctx, 2);
        setState(824);
        match(Sparql11Parser::HAT_LABEL);
        setState(825);
        pathElt();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PathModContext ------------------------------------------------------------------

Sparql11Parser::PathModContext::PathModContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::PathModContext::ASTERISK() {
  return getToken(Sparql11Parser::ASTERISK, 0);
}

tree::TerminalNode* Sparql11Parser::PathModContext::QUESTION_MARK_LABEL() {
  return getToken(Sparql11Parser::QUESTION_MARK_LABEL, 0);
}

tree::TerminalNode* Sparql11Parser::PathModContext::PLUS() {
  return getToken(Sparql11Parser::PLUS, 0);
}

tree::TerminalNode* Sparql11Parser::PathModContext::OPEN_CURLY_BRACE() {
  return getToken(Sparql11Parser::OPEN_CURLY_BRACE, 0);
}

std::vector<Sparql11Parser::IntegerContext *> Sparql11Parser::PathModContext::integer() {
  return getRuleContexts<Sparql11Parser::IntegerContext>();
}

Sparql11Parser::IntegerContext* Sparql11Parser::PathModContext::integer(size_t i) {
  return getRuleContext<Sparql11Parser::IntegerContext>(i);
}

tree::TerminalNode* Sparql11Parser::PathModContext::COMMA() {
  return getToken(Sparql11Parser::COMMA, 0);
}

tree::TerminalNode* Sparql11Parser::PathModContext::CLOSE_CURLY_BRACE() {
  return getToken(Sparql11Parser::CLOSE_CURLY_BRACE, 0);
}


size_t Sparql11Parser::PathModContext::getRuleIndex() const {
  return Sparql11Parser::RulePathMod;
}

antlrcpp::Any Sparql11Parser::PathModContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitPathMod(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::PathModContext* Sparql11Parser::pathMod() {
  PathModContext *_localctx = _tracker.createInstance<PathModContext>(_ctx, getState());
  enterRule(_localctx, 162, Sparql11Parser::RulePathMod);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(849);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::ASTERISK: {
        setState(828);
        match(Sparql11Parser::ASTERISK);
        break;
      }

      case Sparql11Parser::QUESTION_MARK_LABEL: {
        setState(829);
        match(Sparql11Parser::QUESTION_MARK_LABEL);
        break;
      }

      case Sparql11Parser::PLUS: {
        setState(830);
        match(Sparql11Parser::PLUS);
        break;
      }

      case Sparql11Parser::OPEN_CURLY_BRACE: {
        setState(831);
        match(Sparql11Parser::OPEN_CURLY_BRACE);
        setState(847);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case Sparql11Parser::INTEGER: {
            setState(832);
            integer();
            setState(841);
            _errHandler->sync(this);
            switch (_input->LA(1)) {
              case Sparql11Parser::COMMA: {
                setState(833);
                match(Sparql11Parser::COMMA);
                setState(838);
                _errHandler->sync(this);
                switch (_input->LA(1)) {
                  case Sparql11Parser::CLOSE_CURLY_BRACE: {
                    setState(834);
                    match(Sparql11Parser::CLOSE_CURLY_BRACE);
                    break;
                  }

                  case Sparql11Parser::INTEGER: {
                    setState(835);
                    integer();
                    setState(836);
                    match(Sparql11Parser::CLOSE_CURLY_BRACE);
                    break;
                  }

                default:
                  throw NoViableAltException(this);
                }
                break;
              }

              case Sparql11Parser::CLOSE_CURLY_BRACE: {
                setState(840);
                match(Sparql11Parser::CLOSE_CURLY_BRACE);
                break;
              }

            default:
              throw NoViableAltException(this);
            }
            break;
          }

          case Sparql11Parser::COMMA: {
            setState(843);
            match(Sparql11Parser::COMMA);
            setState(844);
            integer();
            setState(845);
            match(Sparql11Parser::CLOSE_CURLY_BRACE);
            break;
          }

        default:
          throw NoViableAltException(this);
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PathPrimaryContext ------------------------------------------------------------------

Sparql11Parser::PathPrimaryContext::PathPrimaryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::IriRefContext* Sparql11Parser::PathPrimaryContext::iriRef() {
  return getRuleContext<Sparql11Parser::IriRefContext>(0);
}

tree::TerminalNode* Sparql11Parser::PathPrimaryContext::A() {
  return getToken(Sparql11Parser::A, 0);
}

tree::TerminalNode* Sparql11Parser::PathPrimaryContext::NOT_SIGN() {
  return getToken(Sparql11Parser::NOT_SIGN, 0);
}

Sparql11Parser::PathNegatedPropertySetContext* Sparql11Parser::PathPrimaryContext::pathNegatedPropertySet() {
  return getRuleContext<Sparql11Parser::PathNegatedPropertySetContext>(0);
}

tree::TerminalNode* Sparql11Parser::PathPrimaryContext::OPEN_BRACE() {
  return getToken(Sparql11Parser::OPEN_BRACE, 0);
}

Sparql11Parser::PathContext* Sparql11Parser::PathPrimaryContext::path() {
  return getRuleContext<Sparql11Parser::PathContext>(0);
}

tree::TerminalNode* Sparql11Parser::PathPrimaryContext::CLOSE_BRACE() {
  return getToken(Sparql11Parser::CLOSE_BRACE, 0);
}


size_t Sparql11Parser::PathPrimaryContext::getRuleIndex() const {
  return Sparql11Parser::RulePathPrimary;
}

antlrcpp::Any Sparql11Parser::PathPrimaryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitPathPrimary(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::PathPrimaryContext* Sparql11Parser::pathPrimary() {
  PathPrimaryContext *_localctx = _tracker.createInstance<PathPrimaryContext>(_ctx, getState());
  enterRule(_localctx, 164, Sparql11Parser::RulePathPrimary);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(859);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::IRI_REF:
      case Sparql11Parser::PNAME_NS:
      case Sparql11Parser::PNAME_LN: {
        enterOuterAlt(_localctx, 1);
        setState(851);
        iriRef();
        break;
      }

      case Sparql11Parser::A: {
        enterOuterAlt(_localctx, 2);
        setState(852);
        match(Sparql11Parser::A);
        break;
      }

      case Sparql11Parser::NOT_SIGN: {
        enterOuterAlt(_localctx, 3);
        setState(853);
        match(Sparql11Parser::NOT_SIGN);
        setState(854);
        pathNegatedPropertySet();
        break;
      }

      case Sparql11Parser::OPEN_BRACE: {
        enterOuterAlt(_localctx, 4);
        setState(855);
        match(Sparql11Parser::OPEN_BRACE);
        setState(856);
        path();
        setState(857);
        match(Sparql11Parser::CLOSE_BRACE);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PathNegatedPropertySetContext ------------------------------------------------------------------

Sparql11Parser::PathNegatedPropertySetContext::PathNegatedPropertySetContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Sparql11Parser::PathOneInPropertySetContext *> Sparql11Parser::PathNegatedPropertySetContext::pathOneInPropertySet() {
  return getRuleContexts<Sparql11Parser::PathOneInPropertySetContext>();
}

Sparql11Parser::PathOneInPropertySetContext* Sparql11Parser::PathNegatedPropertySetContext::pathOneInPropertySet(size_t i) {
  return getRuleContext<Sparql11Parser::PathOneInPropertySetContext>(i);
}

tree::TerminalNode* Sparql11Parser::PathNegatedPropertySetContext::OPEN_BRACE() {
  return getToken(Sparql11Parser::OPEN_BRACE, 0);
}

tree::TerminalNode* Sparql11Parser::PathNegatedPropertySetContext::CLOSE_BRACE() {
  return getToken(Sparql11Parser::CLOSE_BRACE, 0);
}

std::vector<tree::TerminalNode *> Sparql11Parser::PathNegatedPropertySetContext::PIPE() {
  return getTokens(Sparql11Parser::PIPE);
}

tree::TerminalNode* Sparql11Parser::PathNegatedPropertySetContext::PIPE(size_t i) {
  return getToken(Sparql11Parser::PIPE, i);
}


size_t Sparql11Parser::PathNegatedPropertySetContext::getRuleIndex() const {
  return Sparql11Parser::RulePathNegatedPropertySet;
}

antlrcpp::Any Sparql11Parser::PathNegatedPropertySetContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitPathNegatedPropertySet(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::PathNegatedPropertySetContext* Sparql11Parser::pathNegatedPropertySet() {
  PathNegatedPropertySetContext *_localctx = _tracker.createInstance<PathNegatedPropertySetContext>(_ctx, getState());
  enterRule(_localctx, 166, Sparql11Parser::RulePathNegatedPropertySet);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(874);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::A:
      case Sparql11Parser::IRI_REF:
      case Sparql11Parser::PNAME_NS:
      case Sparql11Parser::PNAME_LN:
      case Sparql11Parser::HAT_LABEL: {
        enterOuterAlt(_localctx, 1);
        setState(861);
        pathOneInPropertySet();
        break;
      }

      case Sparql11Parser::OPEN_BRACE: {
        enterOuterAlt(_localctx, 2);
        setState(862);
        match(Sparql11Parser::OPEN_BRACE);
        setState(871);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == Sparql11Parser::A || ((((_la - 77) & ~ 0x3fULL) == 0) &&
          ((1ULL << (_la - 77)) & ((1ULL << (Sparql11Parser::IRI_REF - 77))
          | (1ULL << (Sparql11Parser::PNAME_NS - 77))
          | (1ULL << (Sparql11Parser::PNAME_LN - 77))
          | (1ULL << (Sparql11Parser::HAT_LABEL - 77)))) != 0)) {
          setState(863);
          pathOneInPropertySet();
          setState(868);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == Sparql11Parser::PIPE) {
            setState(864);
            match(Sparql11Parser::PIPE);
            setState(865);
            pathOneInPropertySet();
            setState(870);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(873);
        match(Sparql11Parser::CLOSE_BRACE);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PathOneInPropertySetContext ------------------------------------------------------------------

Sparql11Parser::PathOneInPropertySetContext::PathOneInPropertySetContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::IriRefContext* Sparql11Parser::PathOneInPropertySetContext::iriRef() {
  return getRuleContext<Sparql11Parser::IriRefContext>(0);
}

tree::TerminalNode* Sparql11Parser::PathOneInPropertySetContext::A() {
  return getToken(Sparql11Parser::A, 0);
}

tree::TerminalNode* Sparql11Parser::PathOneInPropertySetContext::HAT_LABEL() {
  return getToken(Sparql11Parser::HAT_LABEL, 0);
}


size_t Sparql11Parser::PathOneInPropertySetContext::getRuleIndex() const {
  return Sparql11Parser::RulePathOneInPropertySet;
}

antlrcpp::Any Sparql11Parser::PathOneInPropertySetContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitPathOneInPropertySet(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::PathOneInPropertySetContext* Sparql11Parser::pathOneInPropertySet() {
  PathOneInPropertySetContext *_localctx = _tracker.createInstance<PathOneInPropertySetContext>(_ctx, getState());
  enterRule(_localctx, 168, Sparql11Parser::RulePathOneInPropertySet);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(883);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::IRI_REF:
      case Sparql11Parser::PNAME_NS:
      case Sparql11Parser::PNAME_LN: {
        enterOuterAlt(_localctx, 1);
        setState(876);
        iriRef();
        break;
      }

      case Sparql11Parser::A: {
        enterOuterAlt(_localctx, 2);
        setState(877);
        match(Sparql11Parser::A);
        break;
      }

      case Sparql11Parser::HAT_LABEL: {
        enterOuterAlt(_localctx, 3);
        setState(878);
        match(Sparql11Parser::HAT_LABEL);
        setState(881);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case Sparql11Parser::IRI_REF:
          case Sparql11Parser::PNAME_NS:
          case Sparql11Parser::PNAME_LN: {
            setState(879);
            iriRef();
            break;
          }

          case Sparql11Parser::A: {
            setState(880);
            match(Sparql11Parser::A);
            break;
          }

        default:
          throw NoViableAltException(this);
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IntegerContext ------------------------------------------------------------------

Sparql11Parser::IntegerContext::IntegerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::IntegerContext::INTEGER() {
  return getToken(Sparql11Parser::INTEGER, 0);
}


size_t Sparql11Parser::IntegerContext::getRuleIndex() const {
  return Sparql11Parser::RuleInteger;
}

antlrcpp::Any Sparql11Parser::IntegerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitInteger(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::IntegerContext* Sparql11Parser::integer() {
  IntegerContext *_localctx = _tracker.createInstance<IntegerContext>(_ctx, getState());
  enterRule(_localctx, 170, Sparql11Parser::RuleInteger);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(885);
    match(Sparql11Parser::INTEGER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TriplesNodeContext ------------------------------------------------------------------

Sparql11Parser::TriplesNodeContext::TriplesNodeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::CollectionContext* Sparql11Parser::TriplesNodeContext::collection() {
  return getRuleContext<Sparql11Parser::CollectionContext>(0);
}

Sparql11Parser::BlankNodePropertyListContext* Sparql11Parser::TriplesNodeContext::blankNodePropertyList() {
  return getRuleContext<Sparql11Parser::BlankNodePropertyListContext>(0);
}


size_t Sparql11Parser::TriplesNodeContext::getRuleIndex() const {
  return Sparql11Parser::RuleTriplesNode;
}

antlrcpp::Any Sparql11Parser::TriplesNodeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitTriplesNode(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::TriplesNodeContext* Sparql11Parser::triplesNode() {
  TriplesNodeContext *_localctx = _tracker.createInstance<TriplesNodeContext>(_ctx, getState());
  enterRule(_localctx, 172, Sparql11Parser::RuleTriplesNode);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(889);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::OPEN_BRACE: {
        enterOuterAlt(_localctx, 1);
        setState(887);
        collection();
        break;
      }

      case Sparql11Parser::OPEN_SQUARE_BRACE: {
        enterOuterAlt(_localctx, 2);
        setState(888);
        blankNodePropertyList();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlankNodePropertyListContext ------------------------------------------------------------------

Sparql11Parser::BlankNodePropertyListContext::BlankNodePropertyListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::BlankNodePropertyListContext::OPEN_SQUARE_BRACE() {
  return getToken(Sparql11Parser::OPEN_SQUARE_BRACE, 0);
}

Sparql11Parser::PropertyListNotEmptyContext* Sparql11Parser::BlankNodePropertyListContext::propertyListNotEmpty() {
  return getRuleContext<Sparql11Parser::PropertyListNotEmptyContext>(0);
}

tree::TerminalNode* Sparql11Parser::BlankNodePropertyListContext::CLOSE_SQUARE_BRACE() {
  return getToken(Sparql11Parser::CLOSE_SQUARE_BRACE, 0);
}


size_t Sparql11Parser::BlankNodePropertyListContext::getRuleIndex() const {
  return Sparql11Parser::RuleBlankNodePropertyList;
}

antlrcpp::Any Sparql11Parser::BlankNodePropertyListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitBlankNodePropertyList(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::BlankNodePropertyListContext* Sparql11Parser::blankNodePropertyList() {
  BlankNodePropertyListContext *_localctx = _tracker.createInstance<BlankNodePropertyListContext>(_ctx, getState());
  enterRule(_localctx, 174, Sparql11Parser::RuleBlankNodePropertyList);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(891);
    match(Sparql11Parser::OPEN_SQUARE_BRACE);
    setState(892);
    propertyListNotEmpty();
    setState(893);
    match(Sparql11Parser::CLOSE_SQUARE_BRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CollectionContext ------------------------------------------------------------------

Sparql11Parser::CollectionContext::CollectionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::CollectionContext::OPEN_BRACE() {
  return getToken(Sparql11Parser::OPEN_BRACE, 0);
}

tree::TerminalNode* Sparql11Parser::CollectionContext::CLOSE_BRACE() {
  return getToken(Sparql11Parser::CLOSE_BRACE, 0);
}

std::vector<Sparql11Parser::GraphNodeContext *> Sparql11Parser::CollectionContext::graphNode() {
  return getRuleContexts<Sparql11Parser::GraphNodeContext>();
}

Sparql11Parser::GraphNodeContext* Sparql11Parser::CollectionContext::graphNode(size_t i) {
  return getRuleContext<Sparql11Parser::GraphNodeContext>(i);
}


size_t Sparql11Parser::CollectionContext::getRuleIndex() const {
  return Sparql11Parser::RuleCollection;
}

antlrcpp::Any Sparql11Parser::CollectionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitCollection(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::CollectionContext* Sparql11Parser::collection() {
  CollectionContext *_localctx = _tracker.createInstance<CollectionContext>(_ctx, getState());
  enterRule(_localctx, 176, Sparql11Parser::RuleCollection);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(895);
    match(Sparql11Parser::OPEN_BRACE);
    setState(897); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(896);
      graphNode();
      setState(899); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (((((_la - 75) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 75)) & ((1ULL << (Sparql11Parser::TRUE - 75))
      | (1ULL << (Sparql11Parser::FALSE - 75))
      | (1ULL << (Sparql11Parser::IRI_REF - 75))
      | (1ULL << (Sparql11Parser::PNAME_NS - 75))
      | (1ULL << (Sparql11Parser::PNAME_LN - 75))
      | (1ULL << (Sparql11Parser::VAR1 - 75))
      | (1ULL << (Sparql11Parser::VAR2 - 75))
      | (1ULL << (Sparql11Parser::INTEGER - 75))
      | (1ULL << (Sparql11Parser::DECIMAL - 75))
      | (1ULL << (Sparql11Parser::DOUBLE - 75))
      | (1ULL << (Sparql11Parser::INTEGER_POSITIVE - 75))
      | (1ULL << (Sparql11Parser::DECIMAL_POSITIVE - 75))
      | (1ULL << (Sparql11Parser::DOUBLE_POSITIVE - 75))
      | (1ULL << (Sparql11Parser::INTEGER_NEGATIVE - 75))
      | (1ULL << (Sparql11Parser::DECIMAL_NEGATIVE - 75))
      | (1ULL << (Sparql11Parser::DOUBLE_NEGATIVE - 75))
      | (1ULL << (Sparql11Parser::STRING_LITERAL1 - 75))
      | (1ULL << (Sparql11Parser::STRING_LITERAL2 - 75))
      | (1ULL << (Sparql11Parser::STRING_LITERAL_LONG1 - 75))
      | (1ULL << (Sparql11Parser::STRING_LITERAL_LONG2 - 75))
      | (1ULL << (Sparql11Parser::BLANK_NODE_LABEL - 75))
      | (1ULL << (Sparql11Parser::OPEN_BRACE - 75))
      | (1ULL << (Sparql11Parser::OPEN_SQUARE_BRACE - 75)))) != 0));
    setState(901);
    match(Sparql11Parser::CLOSE_BRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GraphNodeContext ------------------------------------------------------------------

Sparql11Parser::GraphNodeContext::GraphNodeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::VarOrTermContext* Sparql11Parser::GraphNodeContext::varOrTerm() {
  return getRuleContext<Sparql11Parser::VarOrTermContext>(0);
}

Sparql11Parser::TriplesNodeContext* Sparql11Parser::GraphNodeContext::triplesNode() {
  return getRuleContext<Sparql11Parser::TriplesNodeContext>(0);
}


size_t Sparql11Parser::GraphNodeContext::getRuleIndex() const {
  return Sparql11Parser::RuleGraphNode;
}

antlrcpp::Any Sparql11Parser::GraphNodeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitGraphNode(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::GraphNodeContext* Sparql11Parser::graphNode() {
  GraphNodeContext *_localctx = _tracker.createInstance<GraphNodeContext>(_ctx, getState());
  enterRule(_localctx, 178, Sparql11Parser::RuleGraphNode);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(905);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 104, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(903);
      varOrTerm();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(904);
      triplesNode();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarOrTermContext ------------------------------------------------------------------

Sparql11Parser::VarOrTermContext::VarOrTermContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::VariableContext* Sparql11Parser::VarOrTermContext::variable() {
  return getRuleContext<Sparql11Parser::VariableContext>(0);
}

Sparql11Parser::GraphTermContext* Sparql11Parser::VarOrTermContext::graphTerm() {
  return getRuleContext<Sparql11Parser::GraphTermContext>(0);
}


size_t Sparql11Parser::VarOrTermContext::getRuleIndex() const {
  return Sparql11Parser::RuleVarOrTerm;
}

antlrcpp::Any Sparql11Parser::VarOrTermContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitVarOrTerm(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::VarOrTermContext* Sparql11Parser::varOrTerm() {
  VarOrTermContext *_localctx = _tracker.createInstance<VarOrTermContext>(_ctx, getState());
  enterRule(_localctx, 180, Sparql11Parser::RuleVarOrTerm);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(909);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::VAR1:
      case Sparql11Parser::VAR2: {
        enterOuterAlt(_localctx, 1);
        setState(907);
        variable();
        break;
      }

      case Sparql11Parser::TRUE:
      case Sparql11Parser::FALSE:
      case Sparql11Parser::IRI_REF:
      case Sparql11Parser::PNAME_NS:
      case Sparql11Parser::PNAME_LN:
      case Sparql11Parser::INTEGER:
      case Sparql11Parser::DECIMAL:
      case Sparql11Parser::DOUBLE:
      case Sparql11Parser::INTEGER_POSITIVE:
      case Sparql11Parser::DECIMAL_POSITIVE:
      case Sparql11Parser::DOUBLE_POSITIVE:
      case Sparql11Parser::INTEGER_NEGATIVE:
      case Sparql11Parser::DECIMAL_NEGATIVE:
      case Sparql11Parser::DOUBLE_NEGATIVE:
      case Sparql11Parser::STRING_LITERAL1:
      case Sparql11Parser::STRING_LITERAL2:
      case Sparql11Parser::STRING_LITERAL_LONG1:
      case Sparql11Parser::STRING_LITERAL_LONG2:
      case Sparql11Parser::BLANK_NODE_LABEL:
      case Sparql11Parser::OPEN_BRACE:
      case Sparql11Parser::OPEN_SQUARE_BRACE: {
        enterOuterAlt(_localctx, 2);
        setState(908);
        graphTerm();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarOrIriRefContext ------------------------------------------------------------------

Sparql11Parser::VarOrIriRefContext::VarOrIriRefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::VariableContext* Sparql11Parser::VarOrIriRefContext::variable() {
  return getRuleContext<Sparql11Parser::VariableContext>(0);
}

Sparql11Parser::IriRefContext* Sparql11Parser::VarOrIriRefContext::iriRef() {
  return getRuleContext<Sparql11Parser::IriRefContext>(0);
}


size_t Sparql11Parser::VarOrIriRefContext::getRuleIndex() const {
  return Sparql11Parser::RuleVarOrIriRef;
}

antlrcpp::Any Sparql11Parser::VarOrIriRefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitVarOrIriRef(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::VarOrIriRefContext* Sparql11Parser::varOrIriRef() {
  VarOrIriRefContext *_localctx = _tracker.createInstance<VarOrIriRefContext>(_ctx, getState());
  enterRule(_localctx, 182, Sparql11Parser::RuleVarOrIriRef);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(913);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::VAR1:
      case Sparql11Parser::VAR2: {
        enterOuterAlt(_localctx, 1);
        setState(911);
        variable();
        break;
      }

      case Sparql11Parser::IRI_REF:
      case Sparql11Parser::PNAME_NS:
      case Sparql11Parser::PNAME_LN: {
        enterOuterAlt(_localctx, 2);
        setState(912);
        iriRef();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableContext ------------------------------------------------------------------

Sparql11Parser::VariableContext::VariableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::VariableContext::VAR1() {
  return getToken(Sparql11Parser::VAR1, 0);
}

tree::TerminalNode* Sparql11Parser::VariableContext::VAR2() {
  return getToken(Sparql11Parser::VAR2, 0);
}


size_t Sparql11Parser::VariableContext::getRuleIndex() const {
  return Sparql11Parser::RuleVariable;
}

antlrcpp::Any Sparql11Parser::VariableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitVariable(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::VariableContext* Sparql11Parser::variable() {
  VariableContext *_localctx = _tracker.createInstance<VariableContext>(_ctx, getState());
  enterRule(_localctx, 184, Sparql11Parser::RuleVariable);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(915);
    _la = _input->LA(1);
    if (!(_la == Sparql11Parser::VAR1

    || _la == Sparql11Parser::VAR2)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GraphTermContext ------------------------------------------------------------------

Sparql11Parser::GraphTermContext::GraphTermContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::IriRefContext* Sparql11Parser::GraphTermContext::iriRef() {
  return getRuleContext<Sparql11Parser::IriRefContext>(0);
}

Sparql11Parser::RdfLiteralContext* Sparql11Parser::GraphTermContext::rdfLiteral() {
  return getRuleContext<Sparql11Parser::RdfLiteralContext>(0);
}

Sparql11Parser::NumericLiteralContext* Sparql11Parser::GraphTermContext::numericLiteral() {
  return getRuleContext<Sparql11Parser::NumericLiteralContext>(0);
}

Sparql11Parser::BooleanLiteralContext* Sparql11Parser::GraphTermContext::booleanLiteral() {
  return getRuleContext<Sparql11Parser::BooleanLiteralContext>(0);
}

Sparql11Parser::BlankNodeContext* Sparql11Parser::GraphTermContext::blankNode() {
  return getRuleContext<Sparql11Parser::BlankNodeContext>(0);
}

tree::TerminalNode* Sparql11Parser::GraphTermContext::OPEN_BRACE() {
  return getToken(Sparql11Parser::OPEN_BRACE, 0);
}

tree::TerminalNode* Sparql11Parser::GraphTermContext::CLOSE_BRACE() {
  return getToken(Sparql11Parser::CLOSE_BRACE, 0);
}

std::vector<tree::TerminalNode *> Sparql11Parser::GraphTermContext::WS() {
  return getTokens(Sparql11Parser::WS);
}

tree::TerminalNode* Sparql11Parser::GraphTermContext::WS(size_t i) {
  return getToken(Sparql11Parser::WS, i);
}


size_t Sparql11Parser::GraphTermContext::getRuleIndex() const {
  return Sparql11Parser::RuleGraphTerm;
}

antlrcpp::Any Sparql11Parser::GraphTermContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitGraphTerm(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::GraphTermContext* Sparql11Parser::graphTerm() {
  GraphTermContext *_localctx = _tracker.createInstance<GraphTermContext>(_ctx, getState());
  enterRule(_localctx, 186, Sparql11Parser::RuleGraphTerm);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(930);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::IRI_REF:
      case Sparql11Parser::PNAME_NS:
      case Sparql11Parser::PNAME_LN: {
        enterOuterAlt(_localctx, 1);
        setState(917);
        iriRef();
        break;
      }

      case Sparql11Parser::STRING_LITERAL1:
      case Sparql11Parser::STRING_LITERAL2:
      case Sparql11Parser::STRING_LITERAL_LONG1:
      case Sparql11Parser::STRING_LITERAL_LONG2: {
        enterOuterAlt(_localctx, 2);
        setState(918);
        rdfLiteral();
        break;
      }

      case Sparql11Parser::INTEGER:
      case Sparql11Parser::DECIMAL:
      case Sparql11Parser::DOUBLE:
      case Sparql11Parser::INTEGER_POSITIVE:
      case Sparql11Parser::DECIMAL_POSITIVE:
      case Sparql11Parser::DOUBLE_POSITIVE:
      case Sparql11Parser::INTEGER_NEGATIVE:
      case Sparql11Parser::DECIMAL_NEGATIVE:
      case Sparql11Parser::DOUBLE_NEGATIVE: {
        enterOuterAlt(_localctx, 3);
        setState(919);
        numericLiteral();
        break;
      }

      case Sparql11Parser::TRUE:
      case Sparql11Parser::FALSE: {
        enterOuterAlt(_localctx, 4);
        setState(920);
        booleanLiteral();
        break;
      }

      case Sparql11Parser::BLANK_NODE_LABEL:
      case Sparql11Parser::OPEN_SQUARE_BRACE: {
        enterOuterAlt(_localctx, 5);
        setState(921);
        blankNode();
        break;
      }

      case Sparql11Parser::OPEN_BRACE: {
        enterOuterAlt(_localctx, 6);
        setState(922);
        match(Sparql11Parser::OPEN_BRACE);
        setState(926);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == Sparql11Parser::WS) {
          setState(923);
          match(Sparql11Parser::WS);
          setState(928);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(929);
        match(Sparql11Parser::CLOSE_BRACE);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

Sparql11Parser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::ConditionalOrExpressionContext* Sparql11Parser::ExpressionContext::conditionalOrExpression() {
  return getRuleContext<Sparql11Parser::ConditionalOrExpressionContext>(0);
}


size_t Sparql11Parser::ExpressionContext::getRuleIndex() const {
  return Sparql11Parser::RuleExpression;
}

antlrcpp::Any Sparql11Parser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::ExpressionContext* Sparql11Parser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 188, Sparql11Parser::RuleExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(932);
    conditionalOrExpression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConditionalOrExpressionContext ------------------------------------------------------------------

Sparql11Parser::ConditionalOrExpressionContext::ConditionalOrExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Sparql11Parser::ConditionalAndExpressionContext *> Sparql11Parser::ConditionalOrExpressionContext::conditionalAndExpression() {
  return getRuleContexts<Sparql11Parser::ConditionalAndExpressionContext>();
}

Sparql11Parser::ConditionalAndExpressionContext* Sparql11Parser::ConditionalOrExpressionContext::conditionalAndExpression(size_t i) {
  return getRuleContext<Sparql11Parser::ConditionalAndExpressionContext>(i);
}

std::vector<tree::TerminalNode *> Sparql11Parser::ConditionalOrExpressionContext::OR() {
  return getTokens(Sparql11Parser::OR);
}

tree::TerminalNode* Sparql11Parser::ConditionalOrExpressionContext::OR(size_t i) {
  return getToken(Sparql11Parser::OR, i);
}


size_t Sparql11Parser::ConditionalOrExpressionContext::getRuleIndex() const {
  return Sparql11Parser::RuleConditionalOrExpression;
}

antlrcpp::Any Sparql11Parser::ConditionalOrExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitConditionalOrExpression(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::ConditionalOrExpressionContext* Sparql11Parser::conditionalOrExpression() {
  ConditionalOrExpressionContext *_localctx = _tracker.createInstance<ConditionalOrExpressionContext>(_ctx, getState());
  enterRule(_localctx, 190, Sparql11Parser::RuleConditionalOrExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(934);
    conditionalAndExpression();
    setState(939);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Sparql11Parser::OR) {
      setState(935);
      match(Sparql11Parser::OR);
      setState(936);
      conditionalAndExpression();
      setState(941);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConditionalAndExpressionContext ------------------------------------------------------------------

Sparql11Parser::ConditionalAndExpressionContext::ConditionalAndExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Sparql11Parser::ValueLogicalContext *> Sparql11Parser::ConditionalAndExpressionContext::valueLogical() {
  return getRuleContexts<Sparql11Parser::ValueLogicalContext>();
}

Sparql11Parser::ValueLogicalContext* Sparql11Parser::ConditionalAndExpressionContext::valueLogical(size_t i) {
  return getRuleContext<Sparql11Parser::ValueLogicalContext>(i);
}

std::vector<tree::TerminalNode *> Sparql11Parser::ConditionalAndExpressionContext::AND() {
  return getTokens(Sparql11Parser::AND);
}

tree::TerminalNode* Sparql11Parser::ConditionalAndExpressionContext::AND(size_t i) {
  return getToken(Sparql11Parser::AND, i);
}


size_t Sparql11Parser::ConditionalAndExpressionContext::getRuleIndex() const {
  return Sparql11Parser::RuleConditionalAndExpression;
}

antlrcpp::Any Sparql11Parser::ConditionalAndExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitConditionalAndExpression(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::ConditionalAndExpressionContext* Sparql11Parser::conditionalAndExpression() {
  ConditionalAndExpressionContext *_localctx = _tracker.createInstance<ConditionalAndExpressionContext>(_ctx, getState());
  enterRule(_localctx, 192, Sparql11Parser::RuleConditionalAndExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(942);
    valueLogical();
    setState(947);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Sparql11Parser::AND) {
      setState(943);
      match(Sparql11Parser::AND);
      setState(944);
      valueLogical();
      setState(949);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ValueLogicalContext ------------------------------------------------------------------

Sparql11Parser::ValueLogicalContext::ValueLogicalContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::RelationalExpressionContext* Sparql11Parser::ValueLogicalContext::relationalExpression() {
  return getRuleContext<Sparql11Parser::RelationalExpressionContext>(0);
}


size_t Sparql11Parser::ValueLogicalContext::getRuleIndex() const {
  return Sparql11Parser::RuleValueLogical;
}

antlrcpp::Any Sparql11Parser::ValueLogicalContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitValueLogical(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::ValueLogicalContext* Sparql11Parser::valueLogical() {
  ValueLogicalContext *_localctx = _tracker.createInstance<ValueLogicalContext>(_ctx, getState());
  enterRule(_localctx, 194, Sparql11Parser::RuleValueLogical);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(950);
    relationalExpression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelationalExpressionContext ------------------------------------------------------------------

Sparql11Parser::RelationalExpressionContext::RelationalExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Sparql11Parser::NumericExpressionContext *> Sparql11Parser::RelationalExpressionContext::numericExpression() {
  return getRuleContexts<Sparql11Parser::NumericExpressionContext>();
}

Sparql11Parser::NumericExpressionContext* Sparql11Parser::RelationalExpressionContext::numericExpression(size_t i) {
  return getRuleContext<Sparql11Parser::NumericExpressionContext>(i);
}

tree::TerminalNode* Sparql11Parser::RelationalExpressionContext::EQUAL() {
  return getToken(Sparql11Parser::EQUAL, 0);
}

tree::TerminalNode* Sparql11Parser::RelationalExpressionContext::NOT_EQUAL() {
  return getToken(Sparql11Parser::NOT_EQUAL, 0);
}

tree::TerminalNode* Sparql11Parser::RelationalExpressionContext::LESS() {
  return getToken(Sparql11Parser::LESS, 0);
}

tree::TerminalNode* Sparql11Parser::RelationalExpressionContext::GREATER() {
  return getToken(Sparql11Parser::GREATER, 0);
}

tree::TerminalNode* Sparql11Parser::RelationalExpressionContext::LESS_EQUAL() {
  return getToken(Sparql11Parser::LESS_EQUAL, 0);
}

tree::TerminalNode* Sparql11Parser::RelationalExpressionContext::GREATER_EQUAL() {
  return getToken(Sparql11Parser::GREATER_EQUAL, 0);
}

tree::TerminalNode* Sparql11Parser::RelationalExpressionContext::IN() {
  return getToken(Sparql11Parser::IN, 0);
}

Sparql11Parser::ExpressionListContext* Sparql11Parser::RelationalExpressionContext::expressionList() {
  return getRuleContext<Sparql11Parser::ExpressionListContext>(0);
}

tree::TerminalNode* Sparql11Parser::RelationalExpressionContext::NOT() {
  return getToken(Sparql11Parser::NOT, 0);
}


size_t Sparql11Parser::RelationalExpressionContext::getRuleIndex() const {
  return Sparql11Parser::RuleRelationalExpression;
}

antlrcpp::Any Sparql11Parser::RelationalExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitRelationalExpression(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::RelationalExpressionContext* Sparql11Parser::relationalExpression() {
  RelationalExpressionContext *_localctx = _tracker.createInstance<RelationalExpressionContext>(_ctx, getState());
  enterRule(_localctx, 196, Sparql11Parser::RuleRelationalExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(952);
    numericExpression();
    setState(970);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::EQUAL: {
        setState(953);
        match(Sparql11Parser::EQUAL);
        setState(954);
        numericExpression();
        break;
      }

      case Sparql11Parser::NOT_EQUAL: {
        setState(955);
        match(Sparql11Parser::NOT_EQUAL);
        setState(956);
        numericExpression();
        break;
      }

      case Sparql11Parser::LESS: {
        setState(957);
        match(Sparql11Parser::LESS);
        setState(958);
        numericExpression();
        break;
      }

      case Sparql11Parser::GREATER: {
        setState(959);
        match(Sparql11Parser::GREATER);
        setState(960);
        numericExpression();
        break;
      }

      case Sparql11Parser::LESS_EQUAL: {
        setState(961);
        match(Sparql11Parser::LESS_EQUAL);
        setState(962);
        numericExpression();
        break;
      }

      case Sparql11Parser::GREATER_EQUAL: {
        setState(963);
        match(Sparql11Parser::GREATER_EQUAL);
        setState(964);
        numericExpression();
        break;
      }

      case Sparql11Parser::IN: {
        setState(965);
        match(Sparql11Parser::IN);
        setState(966);
        expressionList();
        break;
      }

      case Sparql11Parser::NOT: {
        setState(967);
        match(Sparql11Parser::NOT);
        setState(968);
        match(Sparql11Parser::IN);
        setState(969);
        expressionList();
        break;
      }

      case Sparql11Parser::AS:
      case Sparql11Parser::AND:
      case Sparql11Parser::OR:
      case Sparql11Parser::SEMICOLON:
      case Sparql11Parser::COMMA:
      case Sparql11Parser::CLOSE_BRACE: {
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumericExpressionContext ------------------------------------------------------------------

Sparql11Parser::NumericExpressionContext::NumericExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::AdditiveExpressionContext* Sparql11Parser::NumericExpressionContext::additiveExpression() {
  return getRuleContext<Sparql11Parser::AdditiveExpressionContext>(0);
}


size_t Sparql11Parser::NumericExpressionContext::getRuleIndex() const {
  return Sparql11Parser::RuleNumericExpression;
}

antlrcpp::Any Sparql11Parser::NumericExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitNumericExpression(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::NumericExpressionContext* Sparql11Parser::numericExpression() {
  NumericExpressionContext *_localctx = _tracker.createInstance<NumericExpressionContext>(_ctx, getState());
  enterRule(_localctx, 198, Sparql11Parser::RuleNumericExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(972);
    additiveExpression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AdditiveExpressionContext ------------------------------------------------------------------

Sparql11Parser::AdditiveExpressionContext::AdditiveExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Sparql11Parser::MultiplicativeExpressionContext *> Sparql11Parser::AdditiveExpressionContext::multiplicativeExpression() {
  return getRuleContexts<Sparql11Parser::MultiplicativeExpressionContext>();
}

Sparql11Parser::MultiplicativeExpressionContext* Sparql11Parser::AdditiveExpressionContext::multiplicativeExpression(size_t i) {
  return getRuleContext<Sparql11Parser::MultiplicativeExpressionContext>(i);
}

std::vector<tree::TerminalNode *> Sparql11Parser::AdditiveExpressionContext::PLUS() {
  return getTokens(Sparql11Parser::PLUS);
}

tree::TerminalNode* Sparql11Parser::AdditiveExpressionContext::PLUS(size_t i) {
  return getToken(Sparql11Parser::PLUS, i);
}

std::vector<tree::TerminalNode *> Sparql11Parser::AdditiveExpressionContext::MINUS() {
  return getTokens(Sparql11Parser::MINUS);
}

tree::TerminalNode* Sparql11Parser::AdditiveExpressionContext::MINUS(size_t i) {
  return getToken(Sparql11Parser::MINUS, i);
}

std::vector<Sparql11Parser::NumericLiteralPositiveContext *> Sparql11Parser::AdditiveExpressionContext::numericLiteralPositive() {
  return getRuleContexts<Sparql11Parser::NumericLiteralPositiveContext>();
}

Sparql11Parser::NumericLiteralPositiveContext* Sparql11Parser::AdditiveExpressionContext::numericLiteralPositive(size_t i) {
  return getRuleContext<Sparql11Parser::NumericLiteralPositiveContext>(i);
}

std::vector<Sparql11Parser::NumericLiteralNegativeContext *> Sparql11Parser::AdditiveExpressionContext::numericLiteralNegative() {
  return getRuleContexts<Sparql11Parser::NumericLiteralNegativeContext>();
}

Sparql11Parser::NumericLiteralNegativeContext* Sparql11Parser::AdditiveExpressionContext::numericLiteralNegative(size_t i) {
  return getRuleContext<Sparql11Parser::NumericLiteralNegativeContext>(i);
}

std::vector<tree::TerminalNode *> Sparql11Parser::AdditiveExpressionContext::ASTERISK() {
  return getTokens(Sparql11Parser::ASTERISK);
}

tree::TerminalNode* Sparql11Parser::AdditiveExpressionContext::ASTERISK(size_t i) {
  return getToken(Sparql11Parser::ASTERISK, i);
}

std::vector<Sparql11Parser::UnaryExpressionContext *> Sparql11Parser::AdditiveExpressionContext::unaryExpression() {
  return getRuleContexts<Sparql11Parser::UnaryExpressionContext>();
}

Sparql11Parser::UnaryExpressionContext* Sparql11Parser::AdditiveExpressionContext::unaryExpression(size_t i) {
  return getRuleContext<Sparql11Parser::UnaryExpressionContext>(i);
}

std::vector<tree::TerminalNode *> Sparql11Parser::AdditiveExpressionContext::DIVIDE() {
  return getTokens(Sparql11Parser::DIVIDE);
}

tree::TerminalNode* Sparql11Parser::AdditiveExpressionContext::DIVIDE(size_t i) {
  return getToken(Sparql11Parser::DIVIDE, i);
}


size_t Sparql11Parser::AdditiveExpressionContext::getRuleIndex() const {
  return Sparql11Parser::RuleAdditiveExpression;
}

antlrcpp::Any Sparql11Parser::AdditiveExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitAdditiveExpression(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::AdditiveExpressionContext* Sparql11Parser::additiveExpression() {
  AdditiveExpressionContext *_localctx = _tracker.createInstance<AdditiveExpressionContext>(_ctx, getState());
  enterRule(_localctx, 200, Sparql11Parser::RuleAdditiveExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(974);
    multiplicativeExpression();
    setState(991);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (((((_la - 86) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 86)) & ((1ULL << (Sparql11Parser::INTEGER_POSITIVE - 86))
      | (1ULL << (Sparql11Parser::DECIMAL_POSITIVE - 86))
      | (1ULL << (Sparql11Parser::DOUBLE_POSITIVE - 86))
      | (1ULL << (Sparql11Parser::INTEGER_NEGATIVE - 86))
      | (1ULL << (Sparql11Parser::DECIMAL_NEGATIVE - 86))
      | (1ULL << (Sparql11Parser::DOUBLE_NEGATIVE - 86))
      | (1ULL << (Sparql11Parser::PLUS - 86))
      | (1ULL << (Sparql11Parser::MINUS - 86)))) != 0)) {
      setState(989);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case Sparql11Parser::PLUS: {
          setState(975);
          match(Sparql11Parser::PLUS);
          setState(976);
          multiplicativeExpression();
          break;
        }

        case Sparql11Parser::MINUS: {
          setState(977);
          match(Sparql11Parser::MINUS);
          setState(978);
          multiplicativeExpression();
          break;
        }

        case Sparql11Parser::INTEGER_POSITIVE:
        case Sparql11Parser::DECIMAL_POSITIVE:
        case Sparql11Parser::DOUBLE_POSITIVE:
        case Sparql11Parser::INTEGER_NEGATIVE:
        case Sparql11Parser::DECIMAL_NEGATIVE:
        case Sparql11Parser::DOUBLE_NEGATIVE: {
          setState(981);
          _errHandler->sync(this);
          switch (_input->LA(1)) {
            case Sparql11Parser::INTEGER_POSITIVE:
            case Sparql11Parser::DECIMAL_POSITIVE:
            case Sparql11Parser::DOUBLE_POSITIVE: {
              setState(979);
              numericLiteralPositive();
              break;
            }

            case Sparql11Parser::INTEGER_NEGATIVE:
            case Sparql11Parser::DECIMAL_NEGATIVE:
            case Sparql11Parser::DOUBLE_NEGATIVE: {
              setState(980);
              numericLiteralNegative();
              break;
            }

          default:
            throw NoViableAltException(this);
          }
          setState(987);
          _errHandler->sync(this);
          switch (_input->LA(1)) {
            case Sparql11Parser::ASTERISK: {
              setState(983);
              match(Sparql11Parser::ASTERISK);
              setState(984);
              unaryExpression();
              break;
            }

            case Sparql11Parser::DIVIDE: {
              setState(985);
              match(Sparql11Parser::DIVIDE);
              setState(986);
              unaryExpression();
              break;
            }

            case Sparql11Parser::IN:
            case Sparql11Parser::NOT:
            case Sparql11Parser::AS:
            case Sparql11Parser::INTEGER_POSITIVE:
            case Sparql11Parser::DECIMAL_POSITIVE:
            case Sparql11Parser::DOUBLE_POSITIVE:
            case Sparql11Parser::INTEGER_NEGATIVE:
            case Sparql11Parser::DECIMAL_NEGATIVE:
            case Sparql11Parser::DOUBLE_NEGATIVE:
            case Sparql11Parser::AND:
            case Sparql11Parser::OR:
            case Sparql11Parser::SEMICOLON:
            case Sparql11Parser::PLUS:
            case Sparql11Parser::MINUS:
            case Sparql11Parser::COMMA:
            case Sparql11Parser::EQUAL:
            case Sparql11Parser::LESS:
            case Sparql11Parser::GREATER:
            case Sparql11Parser::CLOSE_BRACE:
            case Sparql11Parser::LESS_EQUAL:
            case Sparql11Parser::GREATER_EQUAL:
            case Sparql11Parser::NOT_EQUAL: {
              break;
            }

          default:
            throw NoViableAltException(this);
          }
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(993);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MultiplicativeExpressionContext ------------------------------------------------------------------

Sparql11Parser::MultiplicativeExpressionContext::MultiplicativeExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<Sparql11Parser::UnaryExpressionContext *> Sparql11Parser::MultiplicativeExpressionContext::unaryExpression() {
  return getRuleContexts<Sparql11Parser::UnaryExpressionContext>();
}

Sparql11Parser::UnaryExpressionContext* Sparql11Parser::MultiplicativeExpressionContext::unaryExpression(size_t i) {
  return getRuleContext<Sparql11Parser::UnaryExpressionContext>(i);
}

std::vector<tree::TerminalNode *> Sparql11Parser::MultiplicativeExpressionContext::ASTERISK() {
  return getTokens(Sparql11Parser::ASTERISK);
}

tree::TerminalNode* Sparql11Parser::MultiplicativeExpressionContext::ASTERISK(size_t i) {
  return getToken(Sparql11Parser::ASTERISK, i);
}

std::vector<tree::TerminalNode *> Sparql11Parser::MultiplicativeExpressionContext::DIVIDE() {
  return getTokens(Sparql11Parser::DIVIDE);
}

tree::TerminalNode* Sparql11Parser::MultiplicativeExpressionContext::DIVIDE(size_t i) {
  return getToken(Sparql11Parser::DIVIDE, i);
}


size_t Sparql11Parser::MultiplicativeExpressionContext::getRuleIndex() const {
  return Sparql11Parser::RuleMultiplicativeExpression;
}

antlrcpp::Any Sparql11Parser::MultiplicativeExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitMultiplicativeExpression(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::MultiplicativeExpressionContext* Sparql11Parser::multiplicativeExpression() {
  MultiplicativeExpressionContext *_localctx = _tracker.createInstance<MultiplicativeExpressionContext>(_ctx, getState());
  enterRule(_localctx, 202, Sparql11Parser::RuleMultiplicativeExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(994);
    unaryExpression();
    setState(1001);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == Sparql11Parser::ASTERISK

    || _la == Sparql11Parser::DIVIDE) {
      setState(999);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case Sparql11Parser::ASTERISK: {
          setState(995);
          match(Sparql11Parser::ASTERISK);
          setState(996);
          unaryExpression();
          break;
        }

        case Sparql11Parser::DIVIDE: {
          setState(997);
          match(Sparql11Parser::DIVIDE);
          setState(998);
          unaryExpression();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(1003);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnaryExpressionContext ------------------------------------------------------------------

Sparql11Parser::UnaryExpressionContext::UnaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::UnaryExpressionContext::NOT_SIGN() {
  return getToken(Sparql11Parser::NOT_SIGN, 0);
}

Sparql11Parser::PrimaryExpressionContext* Sparql11Parser::UnaryExpressionContext::primaryExpression() {
  return getRuleContext<Sparql11Parser::PrimaryExpressionContext>(0);
}

tree::TerminalNode* Sparql11Parser::UnaryExpressionContext::PLUS() {
  return getToken(Sparql11Parser::PLUS, 0);
}

tree::TerminalNode* Sparql11Parser::UnaryExpressionContext::MINUS() {
  return getToken(Sparql11Parser::MINUS, 0);
}


size_t Sparql11Parser::UnaryExpressionContext::getRuleIndex() const {
  return Sparql11Parser::RuleUnaryExpression;
}

antlrcpp::Any Sparql11Parser::UnaryExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitUnaryExpression(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::UnaryExpressionContext* Sparql11Parser::unaryExpression() {
  UnaryExpressionContext *_localctx = _tracker.createInstance<UnaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 204, Sparql11Parser::RuleUnaryExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(1011);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::NOT_SIGN: {
        enterOuterAlt(_localctx, 1);
        setState(1004);
        match(Sparql11Parser::NOT_SIGN);
        setState(1005);
        primaryExpression();
        break;
      }

      case Sparql11Parser::PLUS: {
        enterOuterAlt(_localctx, 2);
        setState(1006);
        match(Sparql11Parser::PLUS);
        setState(1007);
        primaryExpression();
        break;
      }

      case Sparql11Parser::MINUS: {
        enterOuterAlt(_localctx, 3);
        setState(1008);
        match(Sparql11Parser::MINUS);
        setState(1009);
        primaryExpression();
        break;
      }

      case Sparql11Parser::EXISTS:
      case Sparql11Parser::COUNT:
      case Sparql11Parser::SUM:
      case Sparql11Parser::MIN:
      case Sparql11Parser::MAX:
      case Sparql11Parser::AVG:
      case Sparql11Parser::SAMPLE:
      case Sparql11Parser::GROUP_CONCAT:
      case Sparql11Parser::COALESCE:
      case Sparql11Parser::IF:
      case Sparql11Parser::NOT:
      case Sparql11Parser::STR:
      case Sparql11Parser::LANG:
      case Sparql11Parser::LANGMATCHES:
      case Sparql11Parser::DATATYPE:
      case Sparql11Parser::BOUND:
      case Sparql11Parser::SAMETERM:
      case Sparql11Parser::IRI:
      case Sparql11Parser::URI:
      case Sparql11Parser::BNODE:
      case Sparql11Parser::STRLANG:
      case Sparql11Parser::STRDT:
      case Sparql11Parser::ISIRI:
      case Sparql11Parser::ISURI:
      case Sparql11Parser::ISBLANK:
      case Sparql11Parser::ISLITERAL:
      case Sparql11Parser::ISNUMERIC:
      case Sparql11Parser::REGEX:
      case Sparql11Parser::TRUE:
      case Sparql11Parser::FALSE:
      case Sparql11Parser::IRI_REF:
      case Sparql11Parser::PNAME_NS:
      case Sparql11Parser::PNAME_LN:
      case Sparql11Parser::VAR1:
      case Sparql11Parser::VAR2:
      case Sparql11Parser::INTEGER:
      case Sparql11Parser::DECIMAL:
      case Sparql11Parser::DOUBLE:
      case Sparql11Parser::INTEGER_POSITIVE:
      case Sparql11Parser::DECIMAL_POSITIVE:
      case Sparql11Parser::DOUBLE_POSITIVE:
      case Sparql11Parser::INTEGER_NEGATIVE:
      case Sparql11Parser::DECIMAL_NEGATIVE:
      case Sparql11Parser::DOUBLE_NEGATIVE:
      case Sparql11Parser::STRING_LITERAL1:
      case Sparql11Parser::STRING_LITERAL2:
      case Sparql11Parser::STRING_LITERAL_LONG1:
      case Sparql11Parser::STRING_LITERAL_LONG2:
      case Sparql11Parser::OPEN_BRACE: {
        enterOuterAlt(_localctx, 4);
        setState(1010);
        primaryExpression();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryExpressionContext ------------------------------------------------------------------

Sparql11Parser::PrimaryExpressionContext::PrimaryExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::BrackettedExpressionContext* Sparql11Parser::PrimaryExpressionContext::brackettedExpression() {
  return getRuleContext<Sparql11Parser::BrackettedExpressionContext>(0);
}

Sparql11Parser::BuiltInCallContext* Sparql11Parser::PrimaryExpressionContext::builtInCall() {
  return getRuleContext<Sparql11Parser::BuiltInCallContext>(0);
}

Sparql11Parser::IriRefOrFunctionContext* Sparql11Parser::PrimaryExpressionContext::iriRefOrFunction() {
  return getRuleContext<Sparql11Parser::IriRefOrFunctionContext>(0);
}

Sparql11Parser::RdfLiteralContext* Sparql11Parser::PrimaryExpressionContext::rdfLiteral() {
  return getRuleContext<Sparql11Parser::RdfLiteralContext>(0);
}

Sparql11Parser::NumericLiteralContext* Sparql11Parser::PrimaryExpressionContext::numericLiteral() {
  return getRuleContext<Sparql11Parser::NumericLiteralContext>(0);
}

Sparql11Parser::BooleanLiteralContext* Sparql11Parser::PrimaryExpressionContext::booleanLiteral() {
  return getRuleContext<Sparql11Parser::BooleanLiteralContext>(0);
}

Sparql11Parser::VariableContext* Sparql11Parser::PrimaryExpressionContext::variable() {
  return getRuleContext<Sparql11Parser::VariableContext>(0);
}

Sparql11Parser::AggregateContext* Sparql11Parser::PrimaryExpressionContext::aggregate() {
  return getRuleContext<Sparql11Parser::AggregateContext>(0);
}


size_t Sparql11Parser::PrimaryExpressionContext::getRuleIndex() const {
  return Sparql11Parser::RulePrimaryExpression;
}

antlrcpp::Any Sparql11Parser::PrimaryExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitPrimaryExpression(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::PrimaryExpressionContext* Sparql11Parser::primaryExpression() {
  PrimaryExpressionContext *_localctx = _tracker.createInstance<PrimaryExpressionContext>(_ctx, getState());
  enterRule(_localctx, 206, Sparql11Parser::RulePrimaryExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(1021);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::OPEN_BRACE: {
        enterOuterAlt(_localctx, 1);
        setState(1013);
        brackettedExpression();
        break;
      }

      case Sparql11Parser::EXISTS:
      case Sparql11Parser::COALESCE:
      case Sparql11Parser::IF:
      case Sparql11Parser::NOT:
      case Sparql11Parser::STR:
      case Sparql11Parser::LANG:
      case Sparql11Parser::LANGMATCHES:
      case Sparql11Parser::DATATYPE:
      case Sparql11Parser::BOUND:
      case Sparql11Parser::SAMETERM:
      case Sparql11Parser::IRI:
      case Sparql11Parser::URI:
      case Sparql11Parser::BNODE:
      case Sparql11Parser::STRLANG:
      case Sparql11Parser::STRDT:
      case Sparql11Parser::ISIRI:
      case Sparql11Parser::ISURI:
      case Sparql11Parser::ISBLANK:
      case Sparql11Parser::ISLITERAL:
      case Sparql11Parser::ISNUMERIC:
      case Sparql11Parser::REGEX: {
        enterOuterAlt(_localctx, 2);
        setState(1014);
        builtInCall();
        break;
      }

      case Sparql11Parser::IRI_REF:
      case Sparql11Parser::PNAME_NS:
      case Sparql11Parser::PNAME_LN: {
        enterOuterAlt(_localctx, 3);
        setState(1015);
        iriRefOrFunction();
        break;
      }

      case Sparql11Parser::STRING_LITERAL1:
      case Sparql11Parser::STRING_LITERAL2:
      case Sparql11Parser::STRING_LITERAL_LONG1:
      case Sparql11Parser::STRING_LITERAL_LONG2: {
        enterOuterAlt(_localctx, 4);
        setState(1016);
        rdfLiteral();
        break;
      }

      case Sparql11Parser::INTEGER:
      case Sparql11Parser::DECIMAL:
      case Sparql11Parser::DOUBLE:
      case Sparql11Parser::INTEGER_POSITIVE:
      case Sparql11Parser::DECIMAL_POSITIVE:
      case Sparql11Parser::DOUBLE_POSITIVE:
      case Sparql11Parser::INTEGER_NEGATIVE:
      case Sparql11Parser::DECIMAL_NEGATIVE:
      case Sparql11Parser::DOUBLE_NEGATIVE: {
        enterOuterAlt(_localctx, 5);
        setState(1017);
        numericLiteral();
        break;
      }

      case Sparql11Parser::TRUE:
      case Sparql11Parser::FALSE: {
        enterOuterAlt(_localctx, 6);
        setState(1018);
        booleanLiteral();
        break;
      }

      case Sparql11Parser::VAR1:
      case Sparql11Parser::VAR2: {
        enterOuterAlt(_localctx, 7);
        setState(1019);
        variable();
        break;
      }

      case Sparql11Parser::COUNT:
      case Sparql11Parser::SUM:
      case Sparql11Parser::MIN:
      case Sparql11Parser::MAX:
      case Sparql11Parser::AVG:
      case Sparql11Parser::SAMPLE:
      case Sparql11Parser::GROUP_CONCAT: {
        enterOuterAlt(_localctx, 8);
        setState(1020);
        aggregate();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BrackettedExpressionContext ------------------------------------------------------------------

Sparql11Parser::BrackettedExpressionContext::BrackettedExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::BrackettedExpressionContext::OPEN_BRACE() {
  return getToken(Sparql11Parser::OPEN_BRACE, 0);
}

Sparql11Parser::ExpressionContext* Sparql11Parser::BrackettedExpressionContext::expression() {
  return getRuleContext<Sparql11Parser::ExpressionContext>(0);
}

tree::TerminalNode* Sparql11Parser::BrackettedExpressionContext::CLOSE_BRACE() {
  return getToken(Sparql11Parser::CLOSE_BRACE, 0);
}


size_t Sparql11Parser::BrackettedExpressionContext::getRuleIndex() const {
  return Sparql11Parser::RuleBrackettedExpression;
}

antlrcpp::Any Sparql11Parser::BrackettedExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitBrackettedExpression(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::BrackettedExpressionContext* Sparql11Parser::brackettedExpression() {
  BrackettedExpressionContext *_localctx = _tracker.createInstance<BrackettedExpressionContext>(_ctx, getState());
  enterRule(_localctx, 208, Sparql11Parser::RuleBrackettedExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1023);
    match(Sparql11Parser::OPEN_BRACE);
    setState(1024);
    expression();
    setState(1025);
    match(Sparql11Parser::CLOSE_BRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BuiltInCallContext ------------------------------------------------------------------

Sparql11Parser::BuiltInCallContext::BuiltInCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::BuiltInCallContext::STR() {
  return getToken(Sparql11Parser::STR, 0);
}

tree::TerminalNode* Sparql11Parser::BuiltInCallContext::OPEN_BRACE() {
  return getToken(Sparql11Parser::OPEN_BRACE, 0);
}

std::vector<Sparql11Parser::ExpressionContext *> Sparql11Parser::BuiltInCallContext::expression() {
  return getRuleContexts<Sparql11Parser::ExpressionContext>();
}

Sparql11Parser::ExpressionContext* Sparql11Parser::BuiltInCallContext::expression(size_t i) {
  return getRuleContext<Sparql11Parser::ExpressionContext>(i);
}

tree::TerminalNode* Sparql11Parser::BuiltInCallContext::CLOSE_BRACE() {
  return getToken(Sparql11Parser::CLOSE_BRACE, 0);
}

tree::TerminalNode* Sparql11Parser::BuiltInCallContext::LANG() {
  return getToken(Sparql11Parser::LANG, 0);
}

tree::TerminalNode* Sparql11Parser::BuiltInCallContext::LANGMATCHES() {
  return getToken(Sparql11Parser::LANGMATCHES, 0);
}

std::vector<tree::TerminalNode *> Sparql11Parser::BuiltInCallContext::COMMA() {
  return getTokens(Sparql11Parser::COMMA);
}

tree::TerminalNode* Sparql11Parser::BuiltInCallContext::COMMA(size_t i) {
  return getToken(Sparql11Parser::COMMA, i);
}

tree::TerminalNode* Sparql11Parser::BuiltInCallContext::DATATYPE() {
  return getToken(Sparql11Parser::DATATYPE, 0);
}

tree::TerminalNode* Sparql11Parser::BuiltInCallContext::BOUND() {
  return getToken(Sparql11Parser::BOUND, 0);
}

Sparql11Parser::VariableContext* Sparql11Parser::BuiltInCallContext::variable() {
  return getRuleContext<Sparql11Parser::VariableContext>(0);
}

tree::TerminalNode* Sparql11Parser::BuiltInCallContext::IRI() {
  return getToken(Sparql11Parser::IRI, 0);
}

tree::TerminalNode* Sparql11Parser::BuiltInCallContext::URI() {
  return getToken(Sparql11Parser::URI, 0);
}

tree::TerminalNode* Sparql11Parser::BuiltInCallContext::BNODE() {
  return getToken(Sparql11Parser::BNODE, 0);
}

std::vector<tree::TerminalNode *> Sparql11Parser::BuiltInCallContext::WS() {
  return getTokens(Sparql11Parser::WS);
}

tree::TerminalNode* Sparql11Parser::BuiltInCallContext::WS(size_t i) {
  return getToken(Sparql11Parser::WS, i);
}

tree::TerminalNode* Sparql11Parser::BuiltInCallContext::COALESCE() {
  return getToken(Sparql11Parser::COALESCE, 0);
}

Sparql11Parser::ExpressionListContext* Sparql11Parser::BuiltInCallContext::expressionList() {
  return getRuleContext<Sparql11Parser::ExpressionListContext>(0);
}

tree::TerminalNode* Sparql11Parser::BuiltInCallContext::IF() {
  return getToken(Sparql11Parser::IF, 0);
}

tree::TerminalNode* Sparql11Parser::BuiltInCallContext::STRLANG() {
  return getToken(Sparql11Parser::STRLANG, 0);
}

tree::TerminalNode* Sparql11Parser::BuiltInCallContext::STRDT() {
  return getToken(Sparql11Parser::STRDT, 0);
}

tree::TerminalNode* Sparql11Parser::BuiltInCallContext::SAMETERM() {
  return getToken(Sparql11Parser::SAMETERM, 0);
}

tree::TerminalNode* Sparql11Parser::BuiltInCallContext::ISIRI() {
  return getToken(Sparql11Parser::ISIRI, 0);
}

tree::TerminalNode* Sparql11Parser::BuiltInCallContext::ISURI() {
  return getToken(Sparql11Parser::ISURI, 0);
}

tree::TerminalNode* Sparql11Parser::BuiltInCallContext::ISBLANK() {
  return getToken(Sparql11Parser::ISBLANK, 0);
}

tree::TerminalNode* Sparql11Parser::BuiltInCallContext::ISLITERAL() {
  return getToken(Sparql11Parser::ISLITERAL, 0);
}

tree::TerminalNode* Sparql11Parser::BuiltInCallContext::ISNUMERIC() {
  return getToken(Sparql11Parser::ISNUMERIC, 0);
}

Sparql11Parser::RegexExpressionContext* Sparql11Parser::BuiltInCallContext::regexExpression() {
  return getRuleContext<Sparql11Parser::RegexExpressionContext>(0);
}

Sparql11Parser::ExistsFuncContext* Sparql11Parser::BuiltInCallContext::existsFunc() {
  return getRuleContext<Sparql11Parser::ExistsFuncContext>(0);
}

Sparql11Parser::NotExistsFuncContext* Sparql11Parser::BuiltInCallContext::notExistsFunc() {
  return getRuleContext<Sparql11Parser::NotExistsFuncContext>(0);
}


size_t Sparql11Parser::BuiltInCallContext::getRuleIndex() const {
  return Sparql11Parser::RuleBuiltInCall;
}

antlrcpp::Any Sparql11Parser::BuiltInCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitBuiltInCall(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::BuiltInCallContext* Sparql11Parser::builtInCall() {
  BuiltInCallContext *_localctx = _tracker.createInstance<BuiltInCallContext>(_ctx, getState());
  enterRule(_localctx, 210, Sparql11Parser::RuleBuiltInCall);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(1139);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::STR: {
        enterOuterAlt(_localctx, 1);
        setState(1027);
        match(Sparql11Parser::STR);
        setState(1028);
        match(Sparql11Parser::OPEN_BRACE);
        setState(1029);
        expression();
        setState(1030);
        match(Sparql11Parser::CLOSE_BRACE);
        break;
      }

      case Sparql11Parser::LANG: {
        enterOuterAlt(_localctx, 2);
        setState(1032);
        match(Sparql11Parser::LANG);
        setState(1033);
        match(Sparql11Parser::OPEN_BRACE);
        setState(1034);
        expression();
        setState(1035);
        match(Sparql11Parser::CLOSE_BRACE);
        break;
      }

      case Sparql11Parser::LANGMATCHES: {
        enterOuterAlt(_localctx, 3);
        setState(1037);
        match(Sparql11Parser::LANGMATCHES);
        setState(1038);
        match(Sparql11Parser::OPEN_BRACE);
        setState(1039);
        expression();
        setState(1040);
        match(Sparql11Parser::COMMA);
        setState(1041);
        expression();
        setState(1042);
        match(Sparql11Parser::CLOSE_BRACE);
        break;
      }

      case Sparql11Parser::DATATYPE: {
        enterOuterAlt(_localctx, 4);
        setState(1044);
        match(Sparql11Parser::DATATYPE);
        setState(1045);
        match(Sparql11Parser::OPEN_BRACE);
        setState(1046);
        expression();
        setState(1047);
        match(Sparql11Parser::CLOSE_BRACE);
        break;
      }

      case Sparql11Parser::BOUND: {
        enterOuterAlt(_localctx, 5);
        setState(1049);
        match(Sparql11Parser::BOUND);
        setState(1050);
        match(Sparql11Parser::OPEN_BRACE);
        setState(1051);
        variable();
        setState(1052);
        match(Sparql11Parser::CLOSE_BRACE);
        break;
      }

      case Sparql11Parser::IRI: {
        enterOuterAlt(_localctx, 6);
        setState(1054);
        match(Sparql11Parser::IRI);
        setState(1055);
        match(Sparql11Parser::OPEN_BRACE);
        setState(1056);
        expression();
        setState(1057);
        match(Sparql11Parser::CLOSE_BRACE);
        break;
      }

      case Sparql11Parser::URI: {
        enterOuterAlt(_localctx, 7);
        setState(1059);
        match(Sparql11Parser::URI);
        setState(1060);
        match(Sparql11Parser::OPEN_BRACE);
        setState(1061);
        expression();
        setState(1062);
        match(Sparql11Parser::CLOSE_BRACE);
        break;
      }

      case Sparql11Parser::BNODE: {
        enterOuterAlt(_localctx, 8);
        setState(1064);
        match(Sparql11Parser::BNODE);
        setState(1077);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 121, _ctx)) {
        case 1: {
          setState(1065);
          match(Sparql11Parser::OPEN_BRACE);
          setState(1066);
          variable();
          setState(1067);
          match(Sparql11Parser::CLOSE_BRACE);
          break;
        }

        case 2: {
          setState(1069);
          match(Sparql11Parser::OPEN_BRACE);
          setState(1073);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == Sparql11Parser::WS) {
            setState(1070);
            match(Sparql11Parser::WS);
            setState(1075);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
          setState(1076);
          match(Sparql11Parser::CLOSE_BRACE);
          break;
        }

        }
        break;
      }

      case Sparql11Parser::COALESCE: {
        enterOuterAlt(_localctx, 9);
        setState(1079);
        match(Sparql11Parser::COALESCE);
        setState(1080);
        expressionList();
        break;
      }

      case Sparql11Parser::IF: {
        enterOuterAlt(_localctx, 10);
        setState(1081);
        match(Sparql11Parser::IF);
        setState(1082);
        match(Sparql11Parser::OPEN_BRACE);
        setState(1083);
        expression();
        setState(1084);
        match(Sparql11Parser::COMMA);
        setState(1085);
        expression();
        setState(1086);
        match(Sparql11Parser::COMMA);
        setState(1087);
        expression();
        setState(1088);
        match(Sparql11Parser::CLOSE_BRACE);
        break;
      }

      case Sparql11Parser::STRLANG: {
        enterOuterAlt(_localctx, 11);
        setState(1090);
        match(Sparql11Parser::STRLANG);
        setState(1091);
        match(Sparql11Parser::OPEN_BRACE);
        setState(1092);
        expression();
        setState(1093);
        match(Sparql11Parser::COMMA);
        setState(1094);
        expression();
        setState(1095);
        match(Sparql11Parser::CLOSE_BRACE);
        break;
      }

      case Sparql11Parser::STRDT: {
        enterOuterAlt(_localctx, 12);
        setState(1097);
        match(Sparql11Parser::STRDT);
        setState(1098);
        match(Sparql11Parser::OPEN_BRACE);
        setState(1099);
        expression();
        setState(1100);
        match(Sparql11Parser::COMMA);
        setState(1101);
        expression();
        setState(1102);
        match(Sparql11Parser::CLOSE_BRACE);
        break;
      }

      case Sparql11Parser::SAMETERM: {
        enterOuterAlt(_localctx, 13);
        setState(1104);
        match(Sparql11Parser::SAMETERM);
        setState(1105);
        match(Sparql11Parser::OPEN_BRACE);
        setState(1106);
        expression();
        setState(1107);
        match(Sparql11Parser::COMMA);
        setState(1108);
        expression();
        setState(1109);
        match(Sparql11Parser::CLOSE_BRACE);
        break;
      }

      case Sparql11Parser::ISIRI: {
        enterOuterAlt(_localctx, 14);
        setState(1111);
        match(Sparql11Parser::ISIRI);
        setState(1112);
        match(Sparql11Parser::OPEN_BRACE);
        setState(1113);
        expression();
        setState(1114);
        match(Sparql11Parser::CLOSE_BRACE);
        break;
      }

      case Sparql11Parser::ISURI: {
        enterOuterAlt(_localctx, 15);
        setState(1116);
        match(Sparql11Parser::ISURI);
        setState(1117);
        match(Sparql11Parser::OPEN_BRACE);
        setState(1118);
        expression();
        setState(1119);
        match(Sparql11Parser::CLOSE_BRACE);
        break;
      }

      case Sparql11Parser::ISBLANK: {
        enterOuterAlt(_localctx, 16);
        setState(1121);
        match(Sparql11Parser::ISBLANK);
        setState(1122);
        match(Sparql11Parser::OPEN_BRACE);
        setState(1123);
        expression();
        setState(1124);
        match(Sparql11Parser::CLOSE_BRACE);
        break;
      }

      case Sparql11Parser::ISLITERAL: {
        enterOuterAlt(_localctx, 17);
        setState(1126);
        match(Sparql11Parser::ISLITERAL);
        setState(1127);
        match(Sparql11Parser::OPEN_BRACE);
        setState(1128);
        expression();
        setState(1129);
        match(Sparql11Parser::CLOSE_BRACE);
        break;
      }

      case Sparql11Parser::ISNUMERIC: {
        enterOuterAlt(_localctx, 18);
        setState(1131);
        match(Sparql11Parser::ISNUMERIC);
        setState(1132);
        match(Sparql11Parser::OPEN_BRACE);
        setState(1133);
        expression();
        setState(1134);
        match(Sparql11Parser::CLOSE_BRACE);
        break;
      }

      case Sparql11Parser::REGEX: {
        enterOuterAlt(_localctx, 19);
        setState(1136);
        regexExpression();
        break;
      }

      case Sparql11Parser::EXISTS: {
        enterOuterAlt(_localctx, 20);
        setState(1137);
        existsFunc();
        break;
      }

      case Sparql11Parser::NOT: {
        enterOuterAlt(_localctx, 21);
        setState(1138);
        notExistsFunc();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RegexExpressionContext ------------------------------------------------------------------

Sparql11Parser::RegexExpressionContext::RegexExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::RegexExpressionContext::REGEX() {
  return getToken(Sparql11Parser::REGEX, 0);
}

tree::TerminalNode* Sparql11Parser::RegexExpressionContext::OPEN_BRACE() {
  return getToken(Sparql11Parser::OPEN_BRACE, 0);
}

std::vector<Sparql11Parser::ExpressionContext *> Sparql11Parser::RegexExpressionContext::expression() {
  return getRuleContexts<Sparql11Parser::ExpressionContext>();
}

Sparql11Parser::ExpressionContext* Sparql11Parser::RegexExpressionContext::expression(size_t i) {
  return getRuleContext<Sparql11Parser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> Sparql11Parser::RegexExpressionContext::COMMA() {
  return getTokens(Sparql11Parser::COMMA);
}

tree::TerminalNode* Sparql11Parser::RegexExpressionContext::COMMA(size_t i) {
  return getToken(Sparql11Parser::COMMA, i);
}

tree::TerminalNode* Sparql11Parser::RegexExpressionContext::CLOSE_BRACE() {
  return getToken(Sparql11Parser::CLOSE_BRACE, 0);
}


size_t Sparql11Parser::RegexExpressionContext::getRuleIndex() const {
  return Sparql11Parser::RuleRegexExpression;
}

antlrcpp::Any Sparql11Parser::RegexExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitRegexExpression(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::RegexExpressionContext* Sparql11Parser::regexExpression() {
  RegexExpressionContext *_localctx = _tracker.createInstance<RegexExpressionContext>(_ctx, getState());
  enterRule(_localctx, 212, Sparql11Parser::RuleRegexExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1141);
    match(Sparql11Parser::REGEX);
    setState(1142);
    match(Sparql11Parser::OPEN_BRACE);
    setState(1143);
    expression();
    setState(1144);
    match(Sparql11Parser::COMMA);
    setState(1145);
    expression();
    setState(1148);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Sparql11Parser::COMMA) {
      setState(1146);
      match(Sparql11Parser::COMMA);
      setState(1147);
      expression();
    }
    setState(1150);
    match(Sparql11Parser::CLOSE_BRACE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExistsFuncContext ------------------------------------------------------------------

Sparql11Parser::ExistsFuncContext::ExistsFuncContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::ExistsFuncContext::EXISTS() {
  return getToken(Sparql11Parser::EXISTS, 0);
}

Sparql11Parser::GroupGraphPatternContext* Sparql11Parser::ExistsFuncContext::groupGraphPattern() {
  return getRuleContext<Sparql11Parser::GroupGraphPatternContext>(0);
}


size_t Sparql11Parser::ExistsFuncContext::getRuleIndex() const {
  return Sparql11Parser::RuleExistsFunc;
}

antlrcpp::Any Sparql11Parser::ExistsFuncContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitExistsFunc(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::ExistsFuncContext* Sparql11Parser::existsFunc() {
  ExistsFuncContext *_localctx = _tracker.createInstance<ExistsFuncContext>(_ctx, getState());
  enterRule(_localctx, 214, Sparql11Parser::RuleExistsFunc);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1152);
    match(Sparql11Parser::EXISTS);
    setState(1153);
    groupGraphPattern();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NotExistsFuncContext ------------------------------------------------------------------

Sparql11Parser::NotExistsFuncContext::NotExistsFuncContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::NotExistsFuncContext::NOT() {
  return getToken(Sparql11Parser::NOT, 0);
}

tree::TerminalNode* Sparql11Parser::NotExistsFuncContext::EXISTS() {
  return getToken(Sparql11Parser::EXISTS, 0);
}

Sparql11Parser::GroupGraphPatternContext* Sparql11Parser::NotExistsFuncContext::groupGraphPattern() {
  return getRuleContext<Sparql11Parser::GroupGraphPatternContext>(0);
}


size_t Sparql11Parser::NotExistsFuncContext::getRuleIndex() const {
  return Sparql11Parser::RuleNotExistsFunc;
}

antlrcpp::Any Sparql11Parser::NotExistsFuncContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitNotExistsFunc(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::NotExistsFuncContext* Sparql11Parser::notExistsFunc() {
  NotExistsFuncContext *_localctx = _tracker.createInstance<NotExistsFuncContext>(_ctx, getState());
  enterRule(_localctx, 216, Sparql11Parser::RuleNotExistsFunc);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1155);
    match(Sparql11Parser::NOT);
    setState(1156);
    match(Sparql11Parser::EXISTS);
    setState(1157);
    groupGraphPattern();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AggregateContext ------------------------------------------------------------------

Sparql11Parser::AggregateContext::AggregateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::AggregateContext::COUNT() {
  return getToken(Sparql11Parser::COUNT, 0);
}

tree::TerminalNode* Sparql11Parser::AggregateContext::OPEN_BRACE() {
  return getToken(Sparql11Parser::OPEN_BRACE, 0);
}

tree::TerminalNode* Sparql11Parser::AggregateContext::CLOSE_BRACE() {
  return getToken(Sparql11Parser::CLOSE_BRACE, 0);
}

tree::TerminalNode* Sparql11Parser::AggregateContext::SUM() {
  return getToken(Sparql11Parser::SUM, 0);
}

Sparql11Parser::ExpressionContext* Sparql11Parser::AggregateContext::expression() {
  return getRuleContext<Sparql11Parser::ExpressionContext>(0);
}

tree::TerminalNode* Sparql11Parser::AggregateContext::MIN() {
  return getToken(Sparql11Parser::MIN, 0);
}

tree::TerminalNode* Sparql11Parser::AggregateContext::MAX() {
  return getToken(Sparql11Parser::MAX, 0);
}

tree::TerminalNode* Sparql11Parser::AggregateContext::AVG() {
  return getToken(Sparql11Parser::AVG, 0);
}

tree::TerminalNode* Sparql11Parser::AggregateContext::SAMPLE() {
  return getToken(Sparql11Parser::SAMPLE, 0);
}

tree::TerminalNode* Sparql11Parser::AggregateContext::GROUP_CONCAT() {
  return getToken(Sparql11Parser::GROUP_CONCAT, 0);
}

tree::TerminalNode* Sparql11Parser::AggregateContext::ASTERISK() {
  return getToken(Sparql11Parser::ASTERISK, 0);
}

tree::TerminalNode* Sparql11Parser::AggregateContext::DISTINCT() {
  return getToken(Sparql11Parser::DISTINCT, 0);
}

tree::TerminalNode* Sparql11Parser::AggregateContext::SEMICOLON() {
  return getToken(Sparql11Parser::SEMICOLON, 0);
}

tree::TerminalNode* Sparql11Parser::AggregateContext::SEPARATOR() {
  return getToken(Sparql11Parser::SEPARATOR, 0);
}

tree::TerminalNode* Sparql11Parser::AggregateContext::EQUAL() {
  return getToken(Sparql11Parser::EQUAL, 0);
}

Sparql11Parser::StringContext* Sparql11Parser::AggregateContext::string() {
  return getRuleContext<Sparql11Parser::StringContext>(0);
}


size_t Sparql11Parser::AggregateContext::getRuleIndex() const {
  return Sparql11Parser::RuleAggregate;
}

antlrcpp::Any Sparql11Parser::AggregateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitAggregate(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::AggregateContext* Sparql11Parser::aggregate() {
  AggregateContext *_localctx = _tracker.createInstance<AggregateContext>(_ctx, getState());
  enterRule(_localctx, 218, Sparql11Parser::RuleAggregate);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1223);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::COUNT: {
        setState(1159);
        match(Sparql11Parser::COUNT);
        setState(1160);
        match(Sparql11Parser::OPEN_BRACE);
        setState(1162);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == Sparql11Parser::DISTINCT) {
          setState(1161);
          match(Sparql11Parser::DISTINCT);
        }
        setState(1166);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case Sparql11Parser::ASTERISK: {
            setState(1164);
            match(Sparql11Parser::ASTERISK);
            break;
          }

          case Sparql11Parser::EXISTS:
          case Sparql11Parser::COUNT:
          case Sparql11Parser::SUM:
          case Sparql11Parser::MIN:
          case Sparql11Parser::MAX:
          case Sparql11Parser::AVG:
          case Sparql11Parser::SAMPLE:
          case Sparql11Parser::GROUP_CONCAT:
          case Sparql11Parser::COALESCE:
          case Sparql11Parser::IF:
          case Sparql11Parser::NOT:
          case Sparql11Parser::STR:
          case Sparql11Parser::LANG:
          case Sparql11Parser::LANGMATCHES:
          case Sparql11Parser::DATATYPE:
          case Sparql11Parser::BOUND:
          case Sparql11Parser::SAMETERM:
          case Sparql11Parser::IRI:
          case Sparql11Parser::URI:
          case Sparql11Parser::BNODE:
          case Sparql11Parser::STRLANG:
          case Sparql11Parser::STRDT:
          case Sparql11Parser::ISIRI:
          case Sparql11Parser::ISURI:
          case Sparql11Parser::ISBLANK:
          case Sparql11Parser::ISLITERAL:
          case Sparql11Parser::ISNUMERIC:
          case Sparql11Parser::REGEX:
          case Sparql11Parser::TRUE:
          case Sparql11Parser::FALSE:
          case Sparql11Parser::IRI_REF:
          case Sparql11Parser::PNAME_NS:
          case Sparql11Parser::PNAME_LN:
          case Sparql11Parser::VAR1:
          case Sparql11Parser::VAR2:
          case Sparql11Parser::INTEGER:
          case Sparql11Parser::DECIMAL:
          case Sparql11Parser::DOUBLE:
          case Sparql11Parser::INTEGER_POSITIVE:
          case Sparql11Parser::DECIMAL_POSITIVE:
          case Sparql11Parser::DOUBLE_POSITIVE:
          case Sparql11Parser::INTEGER_NEGATIVE:
          case Sparql11Parser::DECIMAL_NEGATIVE:
          case Sparql11Parser::DOUBLE_NEGATIVE:
          case Sparql11Parser::STRING_LITERAL1:
          case Sparql11Parser::STRING_LITERAL2:
          case Sparql11Parser::STRING_LITERAL_LONG1:
          case Sparql11Parser::STRING_LITERAL_LONG2:
          case Sparql11Parser::PLUS:
          case Sparql11Parser::MINUS:
          case Sparql11Parser::NOT_SIGN:
          case Sparql11Parser::OPEN_BRACE: {
            setState(1165);
            expression();
            break;
          }

        default:
          throw NoViableAltException(this);
        }
        setState(1168);
        match(Sparql11Parser::CLOSE_BRACE);
        break;
      }

      case Sparql11Parser::SUM: {
        setState(1169);
        match(Sparql11Parser::SUM);
        setState(1170);
        match(Sparql11Parser::OPEN_BRACE);
        setState(1172);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == Sparql11Parser::DISTINCT) {
          setState(1171);
          match(Sparql11Parser::DISTINCT);
        }
        setState(1174);
        expression();
        setState(1175);
        match(Sparql11Parser::CLOSE_BRACE);
        break;
      }

      case Sparql11Parser::MIN: {
        setState(1177);
        match(Sparql11Parser::MIN);
        setState(1178);
        match(Sparql11Parser::OPEN_BRACE);
        setState(1180);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == Sparql11Parser::DISTINCT) {
          setState(1179);
          match(Sparql11Parser::DISTINCT);
        }
        setState(1182);
        expression();
        setState(1183);
        match(Sparql11Parser::CLOSE_BRACE);
        break;
      }

      case Sparql11Parser::MAX: {
        setState(1185);
        match(Sparql11Parser::MAX);
        setState(1186);
        match(Sparql11Parser::OPEN_BRACE);
        setState(1188);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == Sparql11Parser::DISTINCT) {
          setState(1187);
          match(Sparql11Parser::DISTINCT);
        }
        setState(1190);
        expression();
        setState(1191);
        match(Sparql11Parser::CLOSE_BRACE);
        break;
      }

      case Sparql11Parser::AVG: {
        setState(1193);
        match(Sparql11Parser::AVG);
        setState(1194);
        match(Sparql11Parser::OPEN_BRACE);
        setState(1196);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == Sparql11Parser::DISTINCT) {
          setState(1195);
          match(Sparql11Parser::DISTINCT);
        }
        setState(1198);
        expression();
        setState(1199);
        match(Sparql11Parser::CLOSE_BRACE);
        break;
      }

      case Sparql11Parser::SAMPLE: {
        setState(1201);
        match(Sparql11Parser::SAMPLE);
        setState(1202);
        match(Sparql11Parser::OPEN_BRACE);
        setState(1204);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == Sparql11Parser::DISTINCT) {
          setState(1203);
          match(Sparql11Parser::DISTINCT);
        }
        setState(1206);
        expression();
        setState(1207);
        match(Sparql11Parser::CLOSE_BRACE);
        break;
      }

      case Sparql11Parser::GROUP_CONCAT: {
        setState(1209);
        match(Sparql11Parser::GROUP_CONCAT);
        setState(1210);
        match(Sparql11Parser::OPEN_BRACE);
        setState(1212);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == Sparql11Parser::DISTINCT) {
          setState(1211);
          match(Sparql11Parser::DISTINCT);
        }
        setState(1214);
        expression();
        setState(1219);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == Sparql11Parser::SEMICOLON) {
          setState(1215);
          match(Sparql11Parser::SEMICOLON);
          setState(1216);
          match(Sparql11Parser::SEPARATOR);
          setState(1217);
          match(Sparql11Parser::EQUAL);
          setState(1218);
          string();
        }
        setState(1221);
        match(Sparql11Parser::CLOSE_BRACE);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IriRefOrFunctionContext ------------------------------------------------------------------

Sparql11Parser::IriRefOrFunctionContext::IriRefOrFunctionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::IriRefContext* Sparql11Parser::IriRefOrFunctionContext::iriRef() {
  return getRuleContext<Sparql11Parser::IriRefContext>(0);
}

Sparql11Parser::ArgListContext* Sparql11Parser::IriRefOrFunctionContext::argList() {
  return getRuleContext<Sparql11Parser::ArgListContext>(0);
}


size_t Sparql11Parser::IriRefOrFunctionContext::getRuleIndex() const {
  return Sparql11Parser::RuleIriRefOrFunction;
}

antlrcpp::Any Sparql11Parser::IriRefOrFunctionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitIriRefOrFunction(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::IriRefOrFunctionContext* Sparql11Parser::iriRefOrFunction() {
  IriRefOrFunctionContext *_localctx = _tracker.createInstance<IriRefOrFunctionContext>(_ctx, getState());
  enterRule(_localctx, 220, Sparql11Parser::RuleIriRefOrFunction);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1225);
    iriRef();
    setState(1227);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == Sparql11Parser::OPEN_BRACE) {
      setState(1226);
      argList();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RdfLiteralContext ------------------------------------------------------------------

Sparql11Parser::RdfLiteralContext::RdfLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::StringContext* Sparql11Parser::RdfLiteralContext::string() {
  return getRuleContext<Sparql11Parser::StringContext>(0);
}

tree::TerminalNode* Sparql11Parser::RdfLiteralContext::LANGTAG() {
  return getToken(Sparql11Parser::LANGTAG, 0);
}

tree::TerminalNode* Sparql11Parser::RdfLiteralContext::REFERENCE() {
  return getToken(Sparql11Parser::REFERENCE, 0);
}

Sparql11Parser::IriRefContext* Sparql11Parser::RdfLiteralContext::iriRef() {
  return getRuleContext<Sparql11Parser::IriRefContext>(0);
}


size_t Sparql11Parser::RdfLiteralContext::getRuleIndex() const {
  return Sparql11Parser::RuleRdfLiteral;
}

antlrcpp::Any Sparql11Parser::RdfLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitRdfLiteral(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::RdfLiteralContext* Sparql11Parser::rdfLiteral() {
  RdfLiteralContext *_localctx = _tracker.createInstance<RdfLiteralContext>(_ctx, getState());
  enterRule(_localctx, 222, Sparql11Parser::RuleRdfLiteral);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1229);
    string();
    setState(1233);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::LANGTAG: {
        setState(1230);
        match(Sparql11Parser::LANGTAG);
        break;
      }

      case Sparql11Parser::REFERENCE: {
        setState(1231);
        match(Sparql11Parser::REFERENCE);
        setState(1232);
        iriRef();
        break;
      }

      case Sparql11Parser::SERVICE:
      case Sparql11Parser::MINUS_P:
      case Sparql11Parser::IN:
      case Sparql11Parser::NOT:
      case Sparql11Parser::OPTIONAL:
      case Sparql11Parser::GRAPH:
      case Sparql11Parser::FILTER:
      case Sparql11Parser::A:
      case Sparql11Parser::AS:
      case Sparql11Parser::TRUE:
      case Sparql11Parser::FALSE:
      case Sparql11Parser::IRI_REF:
      case Sparql11Parser::PNAME_NS:
      case Sparql11Parser::PNAME_LN:
      case Sparql11Parser::VAR1:
      case Sparql11Parser::VAR2:
      case Sparql11Parser::INTEGER:
      case Sparql11Parser::DECIMAL:
      case Sparql11Parser::DOUBLE:
      case Sparql11Parser::INTEGER_POSITIVE:
      case Sparql11Parser::DECIMAL_POSITIVE:
      case Sparql11Parser::DOUBLE_POSITIVE:
      case Sparql11Parser::INTEGER_NEGATIVE:
      case Sparql11Parser::DECIMAL_NEGATIVE:
      case Sparql11Parser::DOUBLE_NEGATIVE:
      case Sparql11Parser::STRING_LITERAL1:
      case Sparql11Parser::STRING_LITERAL2:
      case Sparql11Parser::STRING_LITERAL_LONG1:
      case Sparql11Parser::STRING_LITERAL_LONG2:
      case Sparql11Parser::BLANK_NODE_LABEL:
      case Sparql11Parser::AND:
      case Sparql11Parser::OR:
      case Sparql11Parser::OPEN_CURLY_BRACE:
      case Sparql11Parser::CLOSE_CURLY_BRACE:
      case Sparql11Parser::SEMICOLON:
      case Sparql11Parser::DOT:
      case Sparql11Parser::PLUS:
      case Sparql11Parser::MINUS:
      case Sparql11Parser::ASTERISK:
      case Sparql11Parser::COMMA:
      case Sparql11Parser::NOT_SIGN:
      case Sparql11Parser::DIVIDE:
      case Sparql11Parser::EQUAL:
      case Sparql11Parser::LESS:
      case Sparql11Parser::GREATER:
      case Sparql11Parser::OPEN_BRACE:
      case Sparql11Parser::CLOSE_BRACE:
      case Sparql11Parser::LESS_EQUAL:
      case Sparql11Parser::GREATER_EQUAL:
      case Sparql11Parser::NOT_EQUAL:
      case Sparql11Parser::OPEN_SQUARE_BRACE:
      case Sparql11Parser::CLOSE_SQUARE_BRACE:
      case Sparql11Parser::HAT_LABEL:
      case Sparql11Parser::UNDEF: {
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumericLiteralContext ------------------------------------------------------------------

Sparql11Parser::NumericLiteralContext::NumericLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

Sparql11Parser::NumericLiteralUnsignedContext* Sparql11Parser::NumericLiteralContext::numericLiteralUnsigned() {
  return getRuleContext<Sparql11Parser::NumericLiteralUnsignedContext>(0);
}

Sparql11Parser::NumericLiteralPositiveContext* Sparql11Parser::NumericLiteralContext::numericLiteralPositive() {
  return getRuleContext<Sparql11Parser::NumericLiteralPositiveContext>(0);
}

Sparql11Parser::NumericLiteralNegativeContext* Sparql11Parser::NumericLiteralContext::numericLiteralNegative() {
  return getRuleContext<Sparql11Parser::NumericLiteralNegativeContext>(0);
}


size_t Sparql11Parser::NumericLiteralContext::getRuleIndex() const {
  return Sparql11Parser::RuleNumericLiteral;
}

antlrcpp::Any Sparql11Parser::NumericLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitNumericLiteral(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::NumericLiteralContext* Sparql11Parser::numericLiteral() {
  NumericLiteralContext *_localctx = _tracker.createInstance<NumericLiteralContext>(_ctx, getState());
  enterRule(_localctx, 224, Sparql11Parser::RuleNumericLiteral);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(1238);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::INTEGER:
      case Sparql11Parser::DECIMAL:
      case Sparql11Parser::DOUBLE: {
        enterOuterAlt(_localctx, 1);
        setState(1235);
        numericLiteralUnsigned();
        break;
      }

      case Sparql11Parser::INTEGER_POSITIVE:
      case Sparql11Parser::DECIMAL_POSITIVE:
      case Sparql11Parser::DOUBLE_POSITIVE: {
        enterOuterAlt(_localctx, 2);
        setState(1236);
        numericLiteralPositive();
        break;
      }

      case Sparql11Parser::INTEGER_NEGATIVE:
      case Sparql11Parser::DECIMAL_NEGATIVE:
      case Sparql11Parser::DOUBLE_NEGATIVE: {
        enterOuterAlt(_localctx, 3);
        setState(1237);
        numericLiteralNegative();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumericLiteralUnsignedContext ------------------------------------------------------------------

Sparql11Parser::NumericLiteralUnsignedContext::NumericLiteralUnsignedContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::NumericLiteralUnsignedContext::INTEGER() {
  return getToken(Sparql11Parser::INTEGER, 0);
}

tree::TerminalNode* Sparql11Parser::NumericLiteralUnsignedContext::DECIMAL() {
  return getToken(Sparql11Parser::DECIMAL, 0);
}

tree::TerminalNode* Sparql11Parser::NumericLiteralUnsignedContext::DOUBLE() {
  return getToken(Sparql11Parser::DOUBLE, 0);
}


size_t Sparql11Parser::NumericLiteralUnsignedContext::getRuleIndex() const {
  return Sparql11Parser::RuleNumericLiteralUnsigned;
}

antlrcpp::Any Sparql11Parser::NumericLiteralUnsignedContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitNumericLiteralUnsigned(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::NumericLiteralUnsignedContext* Sparql11Parser::numericLiteralUnsigned() {
  NumericLiteralUnsignedContext *_localctx = _tracker.createInstance<NumericLiteralUnsignedContext>(_ctx, getState());
  enterRule(_localctx, 226, Sparql11Parser::RuleNumericLiteralUnsigned);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1240);
    _la = _input->LA(1);
    if (!(((((_la - 83) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 83)) & ((1ULL << (Sparql11Parser::INTEGER - 83))
      | (1ULL << (Sparql11Parser::DECIMAL - 83))
      | (1ULL << (Sparql11Parser::DOUBLE - 83)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumericLiteralPositiveContext ------------------------------------------------------------------

Sparql11Parser::NumericLiteralPositiveContext::NumericLiteralPositiveContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::NumericLiteralPositiveContext::INTEGER_POSITIVE() {
  return getToken(Sparql11Parser::INTEGER_POSITIVE, 0);
}

tree::TerminalNode* Sparql11Parser::NumericLiteralPositiveContext::DECIMAL_POSITIVE() {
  return getToken(Sparql11Parser::DECIMAL_POSITIVE, 0);
}

tree::TerminalNode* Sparql11Parser::NumericLiteralPositiveContext::DOUBLE_POSITIVE() {
  return getToken(Sparql11Parser::DOUBLE_POSITIVE, 0);
}


size_t Sparql11Parser::NumericLiteralPositiveContext::getRuleIndex() const {
  return Sparql11Parser::RuleNumericLiteralPositive;
}

antlrcpp::Any Sparql11Parser::NumericLiteralPositiveContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitNumericLiteralPositive(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::NumericLiteralPositiveContext* Sparql11Parser::numericLiteralPositive() {
  NumericLiteralPositiveContext *_localctx = _tracker.createInstance<NumericLiteralPositiveContext>(_ctx, getState());
  enterRule(_localctx, 228, Sparql11Parser::RuleNumericLiteralPositive);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1242);
    _la = _input->LA(1);
    if (!(((((_la - 86) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 86)) & ((1ULL << (Sparql11Parser::INTEGER_POSITIVE - 86))
      | (1ULL << (Sparql11Parser::DECIMAL_POSITIVE - 86))
      | (1ULL << (Sparql11Parser::DOUBLE_POSITIVE - 86)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumericLiteralNegativeContext ------------------------------------------------------------------

Sparql11Parser::NumericLiteralNegativeContext::NumericLiteralNegativeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::NumericLiteralNegativeContext::INTEGER_NEGATIVE() {
  return getToken(Sparql11Parser::INTEGER_NEGATIVE, 0);
}

tree::TerminalNode* Sparql11Parser::NumericLiteralNegativeContext::DECIMAL_NEGATIVE() {
  return getToken(Sparql11Parser::DECIMAL_NEGATIVE, 0);
}

tree::TerminalNode* Sparql11Parser::NumericLiteralNegativeContext::DOUBLE_NEGATIVE() {
  return getToken(Sparql11Parser::DOUBLE_NEGATIVE, 0);
}


size_t Sparql11Parser::NumericLiteralNegativeContext::getRuleIndex() const {
  return Sparql11Parser::RuleNumericLiteralNegative;
}

antlrcpp::Any Sparql11Parser::NumericLiteralNegativeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitNumericLiteralNegative(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::NumericLiteralNegativeContext* Sparql11Parser::numericLiteralNegative() {
  NumericLiteralNegativeContext *_localctx = _tracker.createInstance<NumericLiteralNegativeContext>(_ctx, getState());
  enterRule(_localctx, 230, Sparql11Parser::RuleNumericLiteralNegative);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1244);
    _la = _input->LA(1);
    if (!(((((_la - 89) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 89)) & ((1ULL << (Sparql11Parser::INTEGER_NEGATIVE - 89))
      | (1ULL << (Sparql11Parser::DECIMAL_NEGATIVE - 89))
      | (1ULL << (Sparql11Parser::DOUBLE_NEGATIVE - 89)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BooleanLiteralContext ------------------------------------------------------------------

Sparql11Parser::BooleanLiteralContext::BooleanLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::BooleanLiteralContext::TRUE() {
  return getToken(Sparql11Parser::TRUE, 0);
}

tree::TerminalNode* Sparql11Parser::BooleanLiteralContext::FALSE() {
  return getToken(Sparql11Parser::FALSE, 0);
}


size_t Sparql11Parser::BooleanLiteralContext::getRuleIndex() const {
  return Sparql11Parser::RuleBooleanLiteral;
}

antlrcpp::Any Sparql11Parser::BooleanLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitBooleanLiteral(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::BooleanLiteralContext* Sparql11Parser::booleanLiteral() {
  BooleanLiteralContext *_localctx = _tracker.createInstance<BooleanLiteralContext>(_ctx, getState());
  enterRule(_localctx, 232, Sparql11Parser::RuleBooleanLiteral);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1246);
    _la = _input->LA(1);
    if (!(_la == Sparql11Parser::TRUE

    || _la == Sparql11Parser::FALSE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StringContext ------------------------------------------------------------------

Sparql11Parser::StringContext::StringContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::StringContext::STRING_LITERAL1() {
  return getToken(Sparql11Parser::STRING_LITERAL1, 0);
}

tree::TerminalNode* Sparql11Parser::StringContext::STRING_LITERAL2() {
  return getToken(Sparql11Parser::STRING_LITERAL2, 0);
}

tree::TerminalNode* Sparql11Parser::StringContext::STRING_LITERAL_LONG1() {
  return getToken(Sparql11Parser::STRING_LITERAL_LONG1, 0);
}

tree::TerminalNode* Sparql11Parser::StringContext::STRING_LITERAL_LONG2() {
  return getToken(Sparql11Parser::STRING_LITERAL_LONG2, 0);
}


size_t Sparql11Parser::StringContext::getRuleIndex() const {
  return Sparql11Parser::RuleString;
}

antlrcpp::Any Sparql11Parser::StringContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitString(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::StringContext* Sparql11Parser::string() {
  StringContext *_localctx = _tracker.createInstance<StringContext>(_ctx, getState());
  enterRule(_localctx, 234, Sparql11Parser::RuleString);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1248);
    _la = _input->LA(1);
    if (!(((((_la - 92) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 92)) & ((1ULL << (Sparql11Parser::STRING_LITERAL1 - 92))
      | (1ULL << (Sparql11Parser::STRING_LITERAL2 - 92))
      | (1ULL << (Sparql11Parser::STRING_LITERAL_LONG1 - 92))
      | (1ULL << (Sparql11Parser::STRING_LITERAL_LONG2 - 92)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IriRefContext ------------------------------------------------------------------

Sparql11Parser::IriRefContext::IriRefContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::IriRefContext::IRI_REF() {
  return getToken(Sparql11Parser::IRI_REF, 0);
}

Sparql11Parser::PrefixedNameContext* Sparql11Parser::IriRefContext::prefixedName() {
  return getRuleContext<Sparql11Parser::PrefixedNameContext>(0);
}


size_t Sparql11Parser::IriRefContext::getRuleIndex() const {
  return Sparql11Parser::RuleIriRef;
}

antlrcpp::Any Sparql11Parser::IriRefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitIriRef(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::IriRefContext* Sparql11Parser::iriRef() {
  IriRefContext *_localctx = _tracker.createInstance<IriRefContext>(_ctx, getState());
  enterRule(_localctx, 236, Sparql11Parser::RuleIriRef);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(1252);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::IRI_REF: {
        enterOuterAlt(_localctx, 1);
        setState(1250);
        match(Sparql11Parser::IRI_REF);
        break;
      }

      case Sparql11Parser::PNAME_NS:
      case Sparql11Parser::PNAME_LN: {
        enterOuterAlt(_localctx, 2);
        setState(1251);
        prefixedName();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrefixedNameContext ------------------------------------------------------------------

Sparql11Parser::PrefixedNameContext::PrefixedNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::PrefixedNameContext::PNAME_LN() {
  return getToken(Sparql11Parser::PNAME_LN, 0);
}

tree::TerminalNode* Sparql11Parser::PrefixedNameContext::PNAME_NS() {
  return getToken(Sparql11Parser::PNAME_NS, 0);
}


size_t Sparql11Parser::PrefixedNameContext::getRuleIndex() const {
  return Sparql11Parser::RulePrefixedName;
}

antlrcpp::Any Sparql11Parser::PrefixedNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitPrefixedName(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::PrefixedNameContext* Sparql11Parser::prefixedName() {
  PrefixedNameContext *_localctx = _tracker.createInstance<PrefixedNameContext>(_ctx, getState());
  enterRule(_localctx, 238, Sparql11Parser::RulePrefixedName);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1254);
    _la = _input->LA(1);
    if (!(_la == Sparql11Parser::PNAME_NS

    || _la == Sparql11Parser::PNAME_LN)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BlankNodeContext ------------------------------------------------------------------

Sparql11Parser::BlankNodeContext::BlankNodeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* Sparql11Parser::BlankNodeContext::BLANK_NODE_LABEL() {
  return getToken(Sparql11Parser::BLANK_NODE_LABEL, 0);
}

tree::TerminalNode* Sparql11Parser::BlankNodeContext::OPEN_SQUARE_BRACE() {
  return getToken(Sparql11Parser::OPEN_SQUARE_BRACE, 0);
}

tree::TerminalNode* Sparql11Parser::BlankNodeContext::CLOSE_SQUARE_BRACE() {
  return getToken(Sparql11Parser::CLOSE_SQUARE_BRACE, 0);
}

std::vector<tree::TerminalNode *> Sparql11Parser::BlankNodeContext::WS() {
  return getTokens(Sparql11Parser::WS);
}

tree::TerminalNode* Sparql11Parser::BlankNodeContext::WS(size_t i) {
  return getToken(Sparql11Parser::WS, i);
}


size_t Sparql11Parser::BlankNodeContext::getRuleIndex() const {
  return Sparql11Parser::RuleBlankNode;
}

antlrcpp::Any Sparql11Parser::BlankNodeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<Sparql11Visitor*>(visitor))
    return parserVisitor->visitBlankNode(this);
  else
    return visitor->visitChildren(this);
}

Sparql11Parser::BlankNodeContext* Sparql11Parser::blankNode() {
  BlankNodeContext *_localctx = _tracker.createInstance<BlankNodeContext>(_ctx, getState());
  enterRule(_localctx, 240, Sparql11Parser::RuleBlankNode);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(1265);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case Sparql11Parser::BLANK_NODE_LABEL: {
        enterOuterAlt(_localctx, 1);
        setState(1256);
        match(Sparql11Parser::BLANK_NODE_LABEL);
        break;
      }

      case Sparql11Parser::OPEN_SQUARE_BRACE: {
        enterOuterAlt(_localctx, 2);
        setState(1257);
        match(Sparql11Parser::OPEN_SQUARE_BRACE);
        setState(1261);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == Sparql11Parser::WS) {
          setState(1258);
          match(Sparql11Parser::WS);
          setState(1263);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(1264);
        match(Sparql11Parser::CLOSE_SQUARE_BRACE);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> Sparql11Parser::_decisionToDFA;
atn::PredictionContextCache Sparql11Parser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN Sparql11Parser::_atn;
std::vector<uint16_t> Sparql11Parser::_serializedATN;

std::vector<std::string> Sparql11Parser::_ruleNames = {
  "queryUnit", "query", "prologue", "baseDecl", "prefixDecl", "selectQuery", 
  "subSelect", "selectClause", "constructQuery", "describeQuery", "askQuery", 
  "datasetClause", "defaultGraphClause", "namedGraphClause", "sourceSelector", 
  "whereClause", "solutionModifier", "groupClause", "groupCondition", "havingClause", 
  "havingCondition", "orderClause", "orderCondition", "limitOffsetClauses", 
  "limitClause", "offsetClause", "bindingsClause", "bindingValue", "updateUnit", 
  "update", "update1", "load", "clear", "drop", "create", "insertData", 
  "deleteData", "deleteWhere", "modify", "deleteClause", "insertClause", 
  "usingClause", "graphRef", "graphRefAll", "quadPattern", "quadData", "quads", 
  "quadsNotTriples", "triplesTemplate", "groupGraphPattern", "groupGraphPatternSub", 
  "triplesBlock", "graphPatternNotTriples", "optionalGraphPattern", "graphGraphPattern", 
  "serviceGraphPattern", "minusGraphPattern", "groupOrUnionGraphPattern", 
  "filter", "constraint", "functionCall", "argList", "expressionList", "constructTemplate", 
  "constructTriples", "triplesSameSubject", "propertyListNotEmpty", "propertyList", 
  "objectList", "object", "verb", "triplesSameSubjectPath", "propertyListNotEmptyPath", 
  "propertyListPath", "verbPath", "verbSimple", "path", "pathAlternative", 
  "pathSequence", "pathElt", "pathEltOrInverse", "pathMod", "pathPrimary", 
  "pathNegatedPropertySet", "pathOneInPropertySet", "integer", "triplesNode", 
  "blankNodePropertyList", "collection", "graphNode", "varOrTerm", "varOrIriRef", 
  "variable", "graphTerm", "expression", "conditionalOrExpression", "conditionalAndExpression", 
  "valueLogical", "relationalExpression", "numericExpression", "additiveExpression", 
  "multiplicativeExpression", "unaryExpression", "primaryExpression", "brackettedExpression", 
  "builtInCall", "regexExpression", "existsFunc", "notExistsFunc", "aggregate", 
  "iriRefOrFunction", "rdfLiteral", "numericLiteral", "numericLiteralUnsigned", 
  "numericLiteralPositive", "numericLiteralNegative", "booleanLiteral", 
  "string", "iriRef", "prefixedName", "blankNode"
};

std::vector<std::string> Sparql11Parser::_literalNames = {
  "", "'data'", "'modify'", "'delete'", "'insert'", "'into'", "'load'", 
  "'clear'", "'create'", "'silent'", "'drop'", "'default'", "'all'", "'service'", 
  "'minus'", "'exists'", "'unsaid'", "'having'", "'count'", "'sum'", "'min'", 
  "'max'", "'avg'", "'sample'", "'group_concat'", "'separator'", "'using'", 
  "'coalesce'", "'define'", "'if'", "'base'", "'PREFIX'", "'in'", "'not'", 
  "'SELECT'", "'DISTINCT'", "'REDUCED'", "'CONSTRUCT'", "'DESCRIBE'", "'ASK'", 
  "'FROM'", "'named'", "'WHERE'", "'order'", "'group'", "'by'", "'asc'", 
  "'desc'", "'LIMIT'", "'offset'", "'bindings'", "'with'", "'OPTIONAL'", 
  "'graph'", "'UNION'", "'FILTER'", "", "'as'", "'str'", "'lang'", "'langmatches'", 
  "'datatype'", "'bound'", "'sameterm'", "'iri'", "'uri'", "'bnode'", "'strlang'", 
  "'strdt'", "'isiri'", "'isuri'", "'isblank'", "'isliteral'", "'isnumeric'", 
  "'regex'", "'true'", "'false'", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "'^^'", "'&&'", "'|'", "'||'", 
  "", "'{'", "'}'", "';'", "'.'", "'+'", "'-'", "'*'", "','", "'!'", "'/'", 
  "'='", "'<'", "'>'", "'('", "')'", "'<='", "'>='", "'!='", "'['", "']'", 
  "'^'", "'?'", "'undef'"
};

std::vector<std::string> Sparql11Parser::_symbolicNames = {
  "", "DATA", "MODIFY", "DELETE", "INSERT", "INTO", "LOAD", "CLEAR", "CREATE", 
  "SILENT", "DROP", "DEFAULT", "ALL", "SERVICE", "MINUS_P", "EXISTS", "UNSAID", 
  "HAVING", "COUNT", "SUM", "MIN", "MAX", "AVG", "SAMPLE", "GROUP_CONCAT", 
  "SEPARATOR", "USING", "COALESCE", "DEFINE", "IF", "BASE", "PREFIX", "IN", 
  "NOT", "SELECT", "DISTINCT", "REDUCED", "CONSTRUCT", "DESCRIBE", "ASK", 
  "FROM", "NAMED", "WHERE", "ORDER", "GROUP", "BY", "ASC", "DESC", "LIMIT", 
  "OFFSET", "BINDINGS", "WITH", "OPTIONAL", "GRAPH", "UNION", "FILTER", 
  "A", "AS", "STR", "LANG", "LANGMATCHES", "DATATYPE", "BOUND", "SAMETERM", 
  "IRI", "URI", "BNODE", "STRLANG", "STRDT", "ISIRI", "ISURI", "ISBLANK", 
  "ISLITERAL", "ISNUMERIC", "REGEX", "TRUE", "FALSE", "IRI_REF", "PNAME_NS", 
  "PNAME_LN", "VAR1", "VAR2", "LANGTAG", "INTEGER", "DECIMAL", "DOUBLE", 
  "INTEGER_POSITIVE", "DECIMAL_POSITIVE", "DOUBLE_POSITIVE", "INTEGER_NEGATIVE", 
  "DECIMAL_NEGATIVE", "DOUBLE_NEGATIVE", "STRING_LITERAL1", "STRING_LITERAL2", 
  "STRING_LITERAL_LONG1", "STRING_LITERAL_LONG2", "WS", "BLANK_NODE_LABEL", 
  "REFERENCE", "AND", "PIPE", "OR", "COMMENT", "OPEN_CURLY_BRACE", "CLOSE_CURLY_BRACE", 
  "SEMICOLON", "DOT", "PLUS", "MINUS", "ASTERISK", "COMMA", "NOT_SIGN", 
  "DIVIDE", "EQUAL", "LESS", "GREATER", "OPEN_BRACE", "CLOSE_BRACE", "LESS_EQUAL", 
  "GREATER_EQUAL", "NOT_EQUAL", "OPEN_SQUARE_BRACE", "CLOSE_SQUARE_BRACE", 
  "HAT_LABEL", "QUESTION_MARK_LABEL", "UNDEF"
};

dfa::Vocabulary Sparql11Parser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> Sparql11Parser::_tokenNames;

Sparql11Parser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x430, 0xd6d1, 0x8206, 0xad2d, 0x4417, 0xaef1, 0x8d80, 0xaadd, 
    0x3, 0x7f, 0x4f6, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 
    0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 
    0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 
    0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 
    0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 
    0x1f, 0x9, 0x1f, 0x4, 0x20, 0x9, 0x20, 0x4, 0x21, 0x9, 0x21, 0x4, 0x22, 
    0x9, 0x22, 0x4, 0x23, 0x9, 0x23, 0x4, 0x24, 0x9, 0x24, 0x4, 0x25, 0x9, 
    0x25, 0x4, 0x26, 0x9, 0x26, 0x4, 0x27, 0x9, 0x27, 0x4, 0x28, 0x9, 0x28, 
    0x4, 0x29, 0x9, 0x29, 0x4, 0x2a, 0x9, 0x2a, 0x4, 0x2b, 0x9, 0x2b, 0x4, 
    0x2c, 0x9, 0x2c, 0x4, 0x2d, 0x9, 0x2d, 0x4, 0x2e, 0x9, 0x2e, 0x4, 0x2f, 
    0x9, 0x2f, 0x4, 0x30, 0x9, 0x30, 0x4, 0x31, 0x9, 0x31, 0x4, 0x32, 0x9, 
    0x32, 0x4, 0x33, 0x9, 0x33, 0x4, 0x34, 0x9, 0x34, 0x4, 0x35, 0x9, 0x35, 
    0x4, 0x36, 0x9, 0x36, 0x4, 0x37, 0x9, 0x37, 0x4, 0x38, 0x9, 0x38, 0x4, 
    0x39, 0x9, 0x39, 0x4, 0x3a, 0x9, 0x3a, 0x4, 0x3b, 0x9, 0x3b, 0x4, 0x3c, 
    0x9, 0x3c, 0x4, 0x3d, 0x9, 0x3d, 0x4, 0x3e, 0x9, 0x3e, 0x4, 0x3f, 0x9, 
    0x3f, 0x4, 0x40, 0x9, 0x40, 0x4, 0x41, 0x9, 0x41, 0x4, 0x42, 0x9, 0x42, 
    0x4, 0x43, 0x9, 0x43, 0x4, 0x44, 0x9, 0x44, 0x4, 0x45, 0x9, 0x45, 0x4, 
    0x46, 0x9, 0x46, 0x4, 0x47, 0x9, 0x47, 0x4, 0x48, 0x9, 0x48, 0x4, 0x49, 
    0x9, 0x49, 0x4, 0x4a, 0x9, 0x4a, 0x4, 0x4b, 0x9, 0x4b, 0x4, 0x4c, 0x9, 
    0x4c, 0x4, 0x4d, 0x9, 0x4d, 0x4, 0x4e, 0x9, 0x4e, 0x4, 0x4f, 0x9, 0x4f, 
    0x4, 0x50, 0x9, 0x50, 0x4, 0x51, 0x9, 0x51, 0x4, 0x52, 0x9, 0x52, 0x4, 
    0x53, 0x9, 0x53, 0x4, 0x54, 0x9, 0x54, 0x4, 0x55, 0x9, 0x55, 0x4, 0x56, 
    0x9, 0x56, 0x4, 0x57, 0x9, 0x57, 0x4, 0x58, 0x9, 0x58, 0x4, 0x59, 0x9, 
    0x59, 0x4, 0x5a, 0x9, 0x5a, 0x4, 0x5b, 0x9, 0x5b, 0x4, 0x5c, 0x9, 0x5c, 
    0x4, 0x5d, 0x9, 0x5d, 0x4, 0x5e, 0x9, 0x5e, 0x4, 0x5f, 0x9, 0x5f, 0x4, 
    0x60, 0x9, 0x60, 0x4, 0x61, 0x9, 0x61, 0x4, 0x62, 0x9, 0x62, 0x4, 0x63, 
    0x9, 0x63, 0x4, 0x64, 0x9, 0x64, 0x4, 0x65, 0x9, 0x65, 0x4, 0x66, 0x9, 
    0x66, 0x4, 0x67, 0x9, 0x67, 0x4, 0x68, 0x9, 0x68, 0x4, 0x69, 0x9, 0x69, 
    0x4, 0x6a, 0x9, 0x6a, 0x4, 0x6b, 0x9, 0x6b, 0x4, 0x6c, 0x9, 0x6c, 0x4, 
    0x6d, 0x9, 0x6d, 0x4, 0x6e, 0x9, 0x6e, 0x4, 0x6f, 0x9, 0x6f, 0x4, 0x70, 
    0x9, 0x70, 0x4, 0x71, 0x9, 0x71, 0x4, 0x72, 0x9, 0x72, 0x4, 0x73, 0x9, 
    0x73, 0x4, 0x74, 0x9, 0x74, 0x4, 0x75, 0x9, 0x75, 0x4, 0x76, 0x9, 0x76, 
    0x4, 0x77, 0x9, 0x77, 0x4, 0x78, 0x9, 0x78, 0x4, 0x79, 0x9, 0x79, 0x4, 
    0x7a, 0x9, 0x7a, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x3, 0x3, 0x5, 0x3, 0xfc, 0xa, 0x3, 0x3, 0x4, 0x5, 0x4, 0xff, 0xa, 
    0x4, 0x3, 0x4, 0x7, 0x4, 0x102, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x105, 
    0xb, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 
    0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x7, 0x7, 0x110, 0xa, 0x7, 0xc, 0x7, 0xe, 
    0x7, 0x113, 0xb, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 
    0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x11f, 0xa, 
    0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x3, 
    0x9, 0x6, 0x9, 0x128, 0xa, 0x9, 0xd, 0x9, 0xe, 0x9, 0x129, 0x3, 0x9, 
    0x5, 0x9, 0x12d, 0xa, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x7, 0xa, 0x132, 
    0xa, 0xa, 0xc, 0xa, 0xe, 0xa, 0x135, 0xb, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x3, 0xb, 0x3, 0xb, 0x6, 0xb, 0x13c, 0xa, 0xb, 0xd, 0xb, 0xe, 0xb, 
    0x13d, 0x3, 0xb, 0x5, 0xb, 0x141, 0xa, 0xb, 0x3, 0xb, 0x7, 0xb, 0x144, 
    0xa, 0xb, 0xc, 0xb, 0xe, 0xb, 0x147, 0xb, 0xb, 0x3, 0xb, 0x5, 0xb, 0x14a, 
    0xa, 0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 0x7, 0xc, 0x150, 0xa, 
    0xc, 0xc, 0xc, 0xe, 0xc, 0x153, 0xb, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xd, 
    0x3, 0xd, 0x3, 0xd, 0x5, 0xd, 0x15a, 0xa, 0xd, 0x3, 0xe, 0x3, 0xe, 0x3, 
    0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0x10, 0x3, 0x10, 0x3, 0x11, 0x5, 0x11, 
    0x164, 0xa, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x12, 0x5, 0x12, 0x169, 
    0xa, 0x12, 0x3, 0x12, 0x5, 0x12, 0x16c, 0xa, 0x12, 0x3, 0x12, 0x5, 0x12, 
    0x16f, 0xa, 0x12, 0x3, 0x12, 0x5, 0x12, 0x172, 0xa, 0x12, 0x3, 0x13, 
    0x3, 0x13, 0x3, 0x13, 0x6, 0x13, 0x177, 0xa, 0x13, 0xd, 0x13, 0xe, 0x13, 
    0x178, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 
    0x5, 0x14, 0x181, 0xa, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x5, 0x14, 
    0x186, 0xa, 0x14, 0x3, 0x15, 0x3, 0x15, 0x6, 0x15, 0x18a, 0xa, 0x15, 
    0xd, 0x15, 0xe, 0x15, 0x18b, 0x3, 0x16, 0x3, 0x16, 0x3, 0x17, 0x3, 0x17, 
    0x3, 0x17, 0x6, 0x17, 0x193, 0xa, 0x17, 0xd, 0x17, 0xe, 0x17, 0x194, 
    0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x3, 0x18, 0x5, 0x18, 0x19b, 0xa, 0x18, 
    0x5, 0x18, 0x19d, 0xa, 0x18, 0x3, 0x19, 0x3, 0x19, 0x5, 0x19, 0x1a1, 
    0xa, 0x19, 0x3, 0x19, 0x3, 0x19, 0x5, 0x19, 0x1a5, 0xa, 0x19, 0x5, 0x19, 
    0x1a7, 0xa, 0x19, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1b, 0x3, 0x1b, 
    0x3, 0x1b, 0x3, 0x1c, 0x3, 0x1c, 0x7, 0x1c, 0x1b1, 0xa, 0x1c, 0xc, 0x1c, 
    0xe, 0x1c, 0x1b4, 0xb, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x6, 0x1c, 
    0x1b9, 0xa, 0x1c, 0xd, 0x1c, 0xe, 0x1c, 0x1ba, 0x3, 0x1c, 0x3, 0x1c, 
    0x3, 0x1c, 0x3, 0x1c, 0x7, 0x1c, 0x1c1, 0xa, 0x1c, 0xc, 0x1c, 0xe, 0x1c, 
    0x1c4, 0xb, 0x1c, 0x3, 0x1c, 0x7, 0x1c, 0x1c7, 0xa, 0x1c, 0xc, 0x1c, 
    0xe, 0x1c, 0x1ca, 0xb, 0x1c, 0x3, 0x1c, 0x5, 0x1c, 0x1cd, 0xa, 0x1c, 
    0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x5, 0x1d, 0x1d4, 
    0xa, 0x1d, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 
    0x1f, 0x5, 0x1f, 0x1dc, 0xa, 0x1f, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 
    0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x5, 
    0x20, 0x1e7, 0xa, 0x20, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 
    0x5, 0x21, 0x1ed, 0xa, 0x21, 0x3, 0x22, 0x3, 0x22, 0x5, 0x22, 0x1f1, 
    0xa, 0x22, 0x3, 0x22, 0x3, 0x22, 0x3, 0x23, 0x3, 0x23, 0x5, 0x23, 0x1f7, 
    0xa, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x24, 0x3, 0x24, 0x5, 0x24, 0x1fd, 
    0xa, 0x24, 0x3, 0x24, 0x3, 0x24, 0x3, 0x25, 0x3, 0x25, 0x3, 0x25, 0x3, 
    0x25, 0x3, 0x25, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x26, 0x3, 0x27, 
    0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x3, 0x28, 0x3, 0x28, 0x5, 0x28, 0x210, 
    0xa, 0x28, 0x3, 0x28, 0x3, 0x28, 0x5, 0x28, 0x214, 0xa, 0x28, 0x3, 0x28, 
    0x5, 0x28, 0x217, 0xa, 0x28, 0x3, 0x28, 0x7, 0x28, 0x21a, 0xa, 0x28, 
    0xc, 0x28, 0xe, 0x28, 0x21d, 0xb, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 
    0x3, 0x29, 0x3, 0x29, 0x3, 0x29, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 
    0x2b, 0x3, 0x2b, 0x3, 0x2b, 0x3, 0x2b, 0x5, 0x2b, 0x22c, 0xa, 0x2b, 
    0x3, 0x2c, 0x3, 0x2c, 0x5, 0x2c, 0x230, 0xa, 0x2c, 0x3, 0x2d, 0x3, 0x2d, 
    0x3, 0x2d, 0x3, 0x2d, 0x5, 0x2d, 0x236, 0xa, 0x2d, 0x3, 0x2e, 0x3, 0x2e, 
    0x3, 0x2e, 0x3, 0x2e, 0x3, 0x2f, 0x3, 0x2f, 0x3, 0x2f, 0x3, 0x2f, 0x3, 
    0x30, 0x5, 0x30, 0x241, 0xa, 0x30, 0x3, 0x30, 0x3, 0x30, 0x5, 0x30, 
    0x245, 0xa, 0x30, 0x3, 0x30, 0x5, 0x30, 0x248, 0xa, 0x30, 0x7, 0x30, 
    0x24a, 0xa, 0x30, 0xc, 0x30, 0xe, 0x30, 0x24d, 0xb, 0x30, 0x3, 0x31, 
    0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x31, 0x3, 0x32, 0x3, 
    0x32, 0x3, 0x32, 0x5, 0x32, 0x258, 0xa, 0x32, 0x5, 0x32, 0x25a, 0xa, 
    0x32, 0x3, 0x33, 0x3, 0x33, 0x3, 0x33, 0x5, 0x33, 0x25f, 0xa, 0x33, 
    0x3, 0x33, 0x3, 0x33, 0x3, 0x34, 0x5, 0x34, 0x264, 0xa, 0x34, 0x3, 0x34, 
    0x3, 0x34, 0x5, 0x34, 0x268, 0xa, 0x34, 0x3, 0x34, 0x5, 0x34, 0x26b, 
    0xa, 0x34, 0x7, 0x34, 0x26d, 0xa, 0x34, 0xc, 0x34, 0xe, 0x34, 0x270, 
    0xb, 0x34, 0x3, 0x35, 0x3, 0x35, 0x3, 0x35, 0x5, 0x35, 0x275, 0xa, 0x35, 
    0x5, 0x35, 0x277, 0xa, 0x35, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 0x3, 0x36, 
    0x3, 0x36, 0x3, 0x36, 0x5, 0x36, 0x27f, 0xa, 0x36, 0x3, 0x37, 0x3, 0x37, 
    0x3, 0x37, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 0x3, 0x39, 0x3, 
    0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x3a, 0x3, 0x3a, 0x3, 0x3a, 0x3, 0x3b, 
    0x3, 0x3b, 0x3, 0x3b, 0x7, 0x3b, 0x292, 0xa, 0x3b, 0xc, 0x3b, 0xe, 0x3b, 
    0x295, 0xb, 0x3b, 0x3, 0x3c, 0x3, 0x3c, 0x3, 0x3c, 0x3, 0x3d, 0x3, 0x3d, 
    0x3, 0x3d, 0x5, 0x3d, 0x29d, 0xa, 0x3d, 0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 
    0x3, 0x3f, 0x3, 0x3f, 0x7, 0x3f, 0x2a4, 0xa, 0x3f, 0xc, 0x3f, 0xe, 0x3f, 
    0x2a7, 0xb, 0x3f, 0x3, 0x3f, 0x3, 0x3f, 0x3, 0x3f, 0x5, 0x3f, 0x2ac, 
    0xa, 0x3f, 0x3, 0x3f, 0x3, 0x3f, 0x3, 0x3f, 0x7, 0x3f, 0x2b1, 0xa, 0x3f, 
    0xc, 0x3f, 0xe, 0x3f, 0x2b4, 0xb, 0x3f, 0x3, 0x3f, 0x3, 0x3f, 0x5, 0x3f, 
    0x2b8, 0xa, 0x3f, 0x3, 0x40, 0x3, 0x40, 0x7, 0x40, 0x2bc, 0xa, 0x40, 
    0xc, 0x40, 0xe, 0x40, 0x2bf, 0xb, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 
    0x3, 0x40, 0x3, 0x40, 0x7, 0x40, 0x2c6, 0xa, 0x40, 0xc, 0x40, 0xe, 0x40, 
    0x2c9, 0xb, 0x40, 0x3, 0x40, 0x3, 0x40, 0x5, 0x40, 0x2cd, 0xa, 0x40, 
    0x3, 0x41, 0x3, 0x41, 0x5, 0x41, 0x2d1, 0xa, 0x41, 0x3, 0x41, 0x3, 0x41, 
    0x3, 0x42, 0x3, 0x42, 0x3, 0x42, 0x5, 0x42, 0x2d8, 0xa, 0x42, 0x5, 0x42, 
    0x2da, 0xa, 0x42, 0x3, 0x43, 0x3, 0x43, 0x3, 0x43, 0x3, 0x43, 0x3, 0x43, 
    0x3, 0x43, 0x5, 0x43, 0x2e2, 0xa, 0x43, 0x3, 0x44, 0x3, 0x44, 0x3, 0x44, 
    0x3, 0x44, 0x3, 0x44, 0x3, 0x44, 0x5, 0x44, 0x2ea, 0xa, 0x44, 0x7, 0x44, 
    0x2ec, 0xa, 0x44, 0xc, 0x44, 0xe, 0x44, 0x2ef, 0xb, 0x44, 0x3, 0x45, 
    0x5, 0x45, 0x2f2, 0xa, 0x45, 0x3, 0x46, 0x3, 0x46, 0x3, 0x46, 0x7, 0x46, 
    0x2f7, 0xa, 0x46, 0xc, 0x46, 0xe, 0x46, 0x2fa, 0xb, 0x46, 0x3, 0x47, 
    0x3, 0x47, 0x3, 0x48, 0x3, 0x48, 0x5, 0x48, 0x300, 0xa, 0x48, 0x3, 0x49, 
    0x3, 0x49, 0x3, 0x49, 0x3, 0x49, 0x3, 0x49, 0x3, 0x49, 0x5, 0x49, 0x308, 
    0xa, 0x49, 0x3, 0x4a, 0x3, 0x4a, 0x5, 0x4a, 0x30c, 0xa, 0x4a, 0x3, 0x4a, 
    0x3, 0x4a, 0x3, 0x4a, 0x3, 0x4a, 0x5, 0x4a, 0x312, 0xa, 0x4a, 0x3, 0x4a, 
    0x3, 0x4a, 0x5, 0x4a, 0x316, 0xa, 0x4a, 0x7, 0x4a, 0x318, 0xa, 0x4a, 
    0xc, 0x4a, 0xe, 0x4a, 0x31b, 0xb, 0x4a, 0x3, 0x4b, 0x5, 0x4b, 0x31e, 
    0xa, 0x4b, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4d, 0x3, 0x4d, 0x3, 0x4e, 0x3, 
    0x4e, 0x3, 0x4f, 0x3, 0x4f, 0x3, 0x4f, 0x7, 0x4f, 0x329, 0xa, 0x4f, 
    0xc, 0x4f, 0xe, 0x4f, 0x32c, 0xb, 0x4f, 0x3, 0x50, 0x3, 0x50, 0x3, 0x50, 
    0x7, 0x50, 0x331, 0xa, 0x50, 0xc, 0x50, 0xe, 0x50, 0x334, 0xb, 0x50, 
    0x3, 0x51, 0x3, 0x51, 0x5, 0x51, 0x338, 0xa, 0x51, 0x3, 0x52, 0x3, 0x52, 
    0x3, 0x52, 0x5, 0x52, 0x33d, 0xa, 0x52, 0x3, 0x53, 0x3, 0x53, 0x3, 0x53, 
    0x3, 0x53, 0x3, 0x53, 0x3, 0x53, 0x3, 0x53, 0x3, 0x53, 0x3, 0x53, 0x3, 
    0x53, 0x5, 0x53, 0x349, 0xa, 0x53, 0x3, 0x53, 0x5, 0x53, 0x34c, 0xa, 
    0x53, 0x3, 0x53, 0x3, 0x53, 0x3, 0x53, 0x3, 0x53, 0x5, 0x53, 0x352, 
    0xa, 0x53, 0x5, 0x53, 0x354, 0xa, 0x53, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 
    0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 0x5, 0x54, 0x35e, 
    0xa, 0x54, 0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 0x3, 0x55, 0x7, 
    0x55, 0x365, 0xa, 0x55, 0xc, 0x55, 0xe, 0x55, 0x368, 0xb, 0x55, 0x5, 
    0x55, 0x36a, 0xa, 0x55, 0x3, 0x55, 0x5, 0x55, 0x36d, 0xa, 0x55, 0x3, 
    0x56, 0x3, 0x56, 0x3, 0x56, 0x3, 0x56, 0x3, 0x56, 0x5, 0x56, 0x374, 
    0xa, 0x56, 0x5, 0x56, 0x376, 0xa, 0x56, 0x3, 0x57, 0x3, 0x57, 0x3, 0x58, 
    0x3, 0x58, 0x5, 0x58, 0x37c, 0xa, 0x58, 0x3, 0x59, 0x3, 0x59, 0x3, 0x59, 
    0x3, 0x59, 0x3, 0x5a, 0x3, 0x5a, 0x6, 0x5a, 0x384, 0xa, 0x5a, 0xd, 0x5a, 
    0xe, 0x5a, 0x385, 0x3, 0x5a, 0x3, 0x5a, 0x3, 0x5b, 0x3, 0x5b, 0x5, 0x5b, 
    0x38c, 0xa, 0x5b, 0x3, 0x5c, 0x3, 0x5c, 0x5, 0x5c, 0x390, 0xa, 0x5c, 
    0x3, 0x5d, 0x3, 0x5d, 0x5, 0x5d, 0x394, 0xa, 0x5d, 0x3, 0x5e, 0x3, 0x5e, 
    0x3, 0x5f, 0x3, 0x5f, 0x3, 0x5f, 0x3, 0x5f, 0x3, 0x5f, 0x3, 0x5f, 0x3, 
    0x5f, 0x7, 0x5f, 0x39f, 0xa, 0x5f, 0xc, 0x5f, 0xe, 0x5f, 0x3a2, 0xb, 
    0x5f, 0x3, 0x5f, 0x5, 0x5f, 0x3a5, 0xa, 0x5f, 0x3, 0x60, 0x3, 0x60, 
    0x3, 0x61, 0x3, 0x61, 0x3, 0x61, 0x7, 0x61, 0x3ac, 0xa, 0x61, 0xc, 0x61, 
    0xe, 0x61, 0x3af, 0xb, 0x61, 0x3, 0x62, 0x3, 0x62, 0x3, 0x62, 0x7, 0x62, 
    0x3b4, 0xa, 0x62, 0xc, 0x62, 0xe, 0x62, 0x3b7, 0xb, 0x62, 0x3, 0x63, 
    0x3, 0x63, 0x3, 0x64, 0x3, 0x64, 0x3, 0x64, 0x3, 0x64, 0x3, 0x64, 0x3, 
    0x64, 0x3, 0x64, 0x3, 0x64, 0x3, 0x64, 0x3, 0x64, 0x3, 0x64, 0x3, 0x64, 
    0x3, 0x64, 0x3, 0x64, 0x3, 0x64, 0x3, 0x64, 0x3, 0x64, 0x3, 0x64, 0x5, 
    0x64, 0x3cd, 0xa, 0x64, 0x3, 0x65, 0x3, 0x65, 0x3, 0x66, 0x3, 0x66, 
    0x3, 0x66, 0x3, 0x66, 0x3, 0x66, 0x3, 0x66, 0x3, 0x66, 0x5, 0x66, 0x3d8, 
    0xa, 0x66, 0x3, 0x66, 0x3, 0x66, 0x3, 0x66, 0x3, 0x66, 0x5, 0x66, 0x3de, 
    0xa, 0x66, 0x7, 0x66, 0x3e0, 0xa, 0x66, 0xc, 0x66, 0xe, 0x66, 0x3e3, 
    0xb, 0x66, 0x3, 0x67, 0x3, 0x67, 0x3, 0x67, 0x3, 0x67, 0x3, 0x67, 0x7, 
    0x67, 0x3ea, 0xa, 0x67, 0xc, 0x67, 0xe, 0x67, 0x3ed, 0xb, 0x67, 0x3, 
    0x68, 0x3, 0x68, 0x3, 0x68, 0x3, 0x68, 0x3, 0x68, 0x3, 0x68, 0x3, 0x68, 
    0x5, 0x68, 0x3f6, 0xa, 0x68, 0x3, 0x69, 0x3, 0x69, 0x3, 0x69, 0x3, 0x69, 
    0x3, 0x69, 0x3, 0x69, 0x3, 0x69, 0x3, 0x69, 0x5, 0x69, 0x400, 0xa, 0x69, 
    0x3, 0x6a, 0x3, 0x6a, 0x3, 0x6a, 0x3, 0x6a, 0x3, 0x6b, 0x3, 0x6b, 0x3, 
    0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 
    0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 
    0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 
    0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 
    0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 
    0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 
    0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x7, 0x6b, 0x432, 0xa, 0x6b, 0xc, 0x6b, 
    0xe, 0x6b, 0x435, 0xb, 0x6b, 0x3, 0x6b, 0x5, 0x6b, 0x438, 0xa, 0x6b, 
    0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 
    0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 
    0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 
    0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 
    0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 
    0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 
    0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 
    0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 
    0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 0x6b, 0x3, 
    0x6b, 0x3, 0x6b, 0x5, 0x6b, 0x476, 0xa, 0x6b, 0x3, 0x6c, 0x3, 0x6c, 
    0x3, 0x6c, 0x3, 0x6c, 0x3, 0x6c, 0x3, 0x6c, 0x3, 0x6c, 0x5, 0x6c, 0x47f, 
    0xa, 0x6c, 0x3, 0x6c, 0x3, 0x6c, 0x3, 0x6d, 0x3, 0x6d, 0x3, 0x6d, 0x3, 
    0x6e, 0x3, 0x6e, 0x3, 0x6e, 0x3, 0x6e, 0x3, 0x6f, 0x3, 0x6f, 0x3, 0x6f, 
    0x5, 0x6f, 0x48d, 0xa, 0x6f, 0x3, 0x6f, 0x3, 0x6f, 0x5, 0x6f, 0x491, 
    0xa, 0x6f, 0x3, 0x6f, 0x3, 0x6f, 0x3, 0x6f, 0x3, 0x6f, 0x5, 0x6f, 0x497, 
    0xa, 0x6f, 0x3, 0x6f, 0x3, 0x6f, 0x3, 0x6f, 0x3, 0x6f, 0x3, 0x6f, 0x3, 
    0x6f, 0x5, 0x6f, 0x49f, 0xa, 0x6f, 0x3, 0x6f, 0x3, 0x6f, 0x3, 0x6f, 
    0x3, 0x6f, 0x3, 0x6f, 0x3, 0x6f, 0x5, 0x6f, 0x4a7, 0xa, 0x6f, 0x3, 0x6f, 
    0x3, 0x6f, 0x3, 0x6f, 0x3, 0x6f, 0x3, 0x6f, 0x3, 0x6f, 0x5, 0x6f, 0x4af, 
    0xa, 0x6f, 0x3, 0x6f, 0x3, 0x6f, 0x3, 0x6f, 0x3, 0x6f, 0x3, 0x6f, 0x3, 
    0x6f, 0x5, 0x6f, 0x4b7, 0xa, 0x6f, 0x3, 0x6f, 0x3, 0x6f, 0x3, 0x6f, 
    0x3, 0x6f, 0x3, 0x6f, 0x3, 0x6f, 0x5, 0x6f, 0x4bf, 0xa, 0x6f, 0x3, 0x6f, 
    0x3, 0x6f, 0x3, 0x6f, 0x3, 0x6f, 0x3, 0x6f, 0x5, 0x6f, 0x4c6, 0xa, 0x6f, 
    0x3, 0x6f, 0x3, 0x6f, 0x5, 0x6f, 0x4ca, 0xa, 0x6f, 0x3, 0x70, 0x3, 0x70, 
    0x5, 0x70, 0x4ce, 0xa, 0x70, 0x3, 0x71, 0x3, 0x71, 0x3, 0x71, 0x3, 0x71, 
    0x5, 0x71, 0x4d4, 0xa, 0x71, 0x3, 0x72, 0x3, 0x72, 0x3, 0x72, 0x5, 0x72, 
    0x4d9, 0xa, 0x72, 0x3, 0x73, 0x3, 0x73, 0x3, 0x74, 0x3, 0x74, 0x3, 0x75, 
    0x3, 0x75, 0x3, 0x76, 0x3, 0x76, 0x3, 0x77, 0x3, 0x77, 0x3, 0x78, 0x3, 
    0x78, 0x5, 0x78, 0x4e7, 0xa, 0x78, 0x3, 0x79, 0x3, 0x79, 0x3, 0x7a, 
    0x3, 0x7a, 0x3, 0x7a, 0x7, 0x7a, 0x4ee, 0xa, 0x7a, 0xc, 0x7a, 0xe, 0x7a, 
    0x4f1, 0xb, 0x7a, 0x3, 0x7a, 0x5, 0x7a, 0x4f4, 0xa, 0x7a, 0x3, 0x7a, 
    0x2, 0x2, 0x7b, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 
    0x16, 0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 
    0x2e, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e, 0x40, 0x42, 0x44, 
    0x46, 0x48, 0x4a, 0x4c, 0x4e, 0x50, 0x52, 0x54, 0x56, 0x58, 0x5a, 0x5c, 
    0x5e, 0x60, 0x62, 0x64, 0x66, 0x68, 0x6a, 0x6c, 0x6e, 0x70, 0x72, 0x74, 
    0x76, 0x78, 0x7a, 0x7c, 0x7e, 0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c, 
    0x8e, 0x90, 0x92, 0x94, 0x96, 0x98, 0x9a, 0x9c, 0x9e, 0xa0, 0xa2, 0xa4, 
    0xa6, 0xa8, 0xaa, 0xac, 0xae, 0xb0, 0xb2, 0xb4, 0xb6, 0xb8, 0xba, 0xbc, 
    0xbe, 0xc0, 0xc2, 0xc4, 0xc6, 0xc8, 0xca, 0xcc, 0xce, 0xd0, 0xd2, 0xd4, 
    0xd6, 0xd8, 0xda, 0xdc, 0xde, 0xe0, 0xe2, 0xe4, 0xe6, 0xe8, 0xea, 0xec, 
    0xee, 0xf0, 0xf2, 0x2, 0xb, 0x3, 0x2, 0x25, 0x26, 0x3, 0x2, 0x30, 0x31, 
    0x3, 0x2, 0x52, 0x53, 0x3, 0x2, 0x55, 0x57, 0x3, 0x2, 0x58, 0x5a, 0x3, 
    0x2, 0x5b, 0x5d, 0x3, 0x2, 0x4d, 0x4e, 0x3, 0x2, 0x5e, 0x61, 0x3, 0x2, 
    0x50, 0x51, 0x551, 0x2, 0xf4, 0x3, 0x2, 0x2, 0x2, 0x4, 0xf6, 0x3, 0x2, 
    0x2, 0x2, 0x6, 0xfe, 0x3, 0x2, 0x2, 0x2, 0x8, 0x106, 0x3, 0x2, 0x2, 
    0x2, 0xa, 0x109, 0x3, 0x2, 0x2, 0x2, 0xc, 0x10d, 0x3, 0x2, 0x2, 0x2, 
    0xe, 0x118, 0x3, 0x2, 0x2, 0x2, 0x10, 0x11c, 0x3, 0x2, 0x2, 0x2, 0x12, 
    0x12e, 0x3, 0x2, 0x2, 0x2, 0x14, 0x139, 0x3, 0x2, 0x2, 0x2, 0x16, 0x14d, 
    0x3, 0x2, 0x2, 0x2, 0x18, 0x156, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x15b, 0x3, 
    0x2, 0x2, 0x2, 0x1c, 0x15d, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x160, 0x3, 0x2, 
    0x2, 0x2, 0x20, 0x163, 0x3, 0x2, 0x2, 0x2, 0x22, 0x168, 0x3, 0x2, 0x2, 
    0x2, 0x24, 0x173, 0x3, 0x2, 0x2, 0x2, 0x26, 0x185, 0x3, 0x2, 0x2, 0x2, 
    0x28, 0x187, 0x3, 0x2, 0x2, 0x2, 0x2a, 0x18d, 0x3, 0x2, 0x2, 0x2, 0x2c, 
    0x18f, 0x3, 0x2, 0x2, 0x2, 0x2e, 0x19c, 0x3, 0x2, 0x2, 0x2, 0x30, 0x1a6, 
    0x3, 0x2, 0x2, 0x2, 0x32, 0x1a8, 0x3, 0x2, 0x2, 0x2, 0x34, 0x1ab, 0x3, 
    0x2, 0x2, 0x2, 0x36, 0x1cc, 0x3, 0x2, 0x2, 0x2, 0x38, 0x1d3, 0x3, 0x2, 
    0x2, 0x2, 0x3a, 0x1d5, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x1d7, 0x3, 0x2, 0x2, 
    0x2, 0x3e, 0x1e6, 0x3, 0x2, 0x2, 0x2, 0x40, 0x1e8, 0x3, 0x2, 0x2, 0x2, 
    0x42, 0x1ee, 0x3, 0x2, 0x2, 0x2, 0x44, 0x1f4, 0x3, 0x2, 0x2, 0x2, 0x46, 
    0x1fa, 0x3, 0x2, 0x2, 0x2, 0x48, 0x200, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x205, 
    0x3, 0x2, 0x2, 0x2, 0x4c, 0x209, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x20f, 0x3, 
    0x2, 0x2, 0x2, 0x50, 0x221, 0x3, 0x2, 0x2, 0x2, 0x52, 0x224, 0x3, 0x2, 
    0x2, 0x2, 0x54, 0x227, 0x3, 0x2, 0x2, 0x2, 0x56, 0x22f, 0x3, 0x2, 0x2, 
    0x2, 0x58, 0x235, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x237, 0x3, 0x2, 0x2, 0x2, 
    0x5c, 0x23b, 0x3, 0x2, 0x2, 0x2, 0x5e, 0x240, 0x3, 0x2, 0x2, 0x2, 0x60, 
    0x24e, 0x3, 0x2, 0x2, 0x2, 0x62, 0x254, 0x3, 0x2, 0x2, 0x2, 0x64, 0x25b, 
    0x3, 0x2, 0x2, 0x2, 0x66, 0x263, 0x3, 0x2, 0x2, 0x2, 0x68, 0x271, 0x3, 
    0x2, 0x2, 0x2, 0x6a, 0x27e, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x280, 0x3, 0x2, 
    0x2, 0x2, 0x6e, 0x283, 0x3, 0x2, 0x2, 0x2, 0x70, 0x287, 0x3, 0x2, 0x2, 
    0x2, 0x72, 0x28b, 0x3, 0x2, 0x2, 0x2, 0x74, 0x28e, 0x3, 0x2, 0x2, 0x2, 
    0x76, 0x296, 0x3, 0x2, 0x2, 0x2, 0x78, 0x29c, 0x3, 0x2, 0x2, 0x2, 0x7a, 
    0x29e, 0x3, 0x2, 0x2, 0x2, 0x7c, 0x2b7, 0x3, 0x2, 0x2, 0x2, 0x7e, 0x2cc, 
    0x3, 0x2, 0x2, 0x2, 0x80, 0x2ce, 0x3, 0x2, 0x2, 0x2, 0x82, 0x2d4, 0x3, 
    0x2, 0x2, 0x2, 0x84, 0x2e1, 0x3, 0x2, 0x2, 0x2, 0x86, 0x2e3, 0x3, 0x2, 
    0x2, 0x2, 0x88, 0x2f1, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x2f3, 0x3, 0x2, 0x2, 
    0x2, 0x8c, 0x2fb, 0x3, 0x2, 0x2, 0x2, 0x8e, 0x2ff, 0x3, 0x2, 0x2, 0x2, 
    0x90, 0x307, 0x3, 0x2, 0x2, 0x2, 0x92, 0x30b, 0x3, 0x2, 0x2, 0x2, 0x94, 
    0x31d, 0x3, 0x2, 0x2, 0x2, 0x96, 0x31f, 0x3, 0x2, 0x2, 0x2, 0x98, 0x321, 
    0x3, 0x2, 0x2, 0x2, 0x9a, 0x323, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x325, 0x3, 
    0x2, 0x2, 0x2, 0x9e, 0x32d, 0x3, 0x2, 0x2, 0x2, 0xa0, 0x335, 0x3, 0x2, 
    0x2, 0x2, 0xa2, 0x33c, 0x3, 0x2, 0x2, 0x2, 0xa4, 0x353, 0x3, 0x2, 0x2, 
    0x2, 0xa6, 0x35d, 0x3, 0x2, 0x2, 0x2, 0xa8, 0x36c, 0x3, 0x2, 0x2, 0x2, 
    0xaa, 0x375, 0x3, 0x2, 0x2, 0x2, 0xac, 0x377, 0x3, 0x2, 0x2, 0x2, 0xae, 
    0x37b, 0x3, 0x2, 0x2, 0x2, 0xb0, 0x37d, 0x3, 0x2, 0x2, 0x2, 0xb2, 0x381, 
    0x3, 0x2, 0x2, 0x2, 0xb4, 0x38b, 0x3, 0x2, 0x2, 0x2, 0xb6, 0x38f, 0x3, 
    0x2, 0x2, 0x2, 0xb8, 0x393, 0x3, 0x2, 0x2, 0x2, 0xba, 0x395, 0x3, 0x2, 
    0x2, 0x2, 0xbc, 0x3a4, 0x3, 0x2, 0x2, 0x2, 0xbe, 0x3a6, 0x3, 0x2, 0x2, 
    0x2, 0xc0, 0x3a8, 0x3, 0x2, 0x2, 0x2, 0xc2, 0x3b0, 0x3, 0x2, 0x2, 0x2, 
    0xc4, 0x3b8, 0x3, 0x2, 0x2, 0x2, 0xc6, 0x3ba, 0x3, 0x2, 0x2, 0x2, 0xc8, 
    0x3ce, 0x3, 0x2, 0x2, 0x2, 0xca, 0x3d0, 0x3, 0x2, 0x2, 0x2, 0xcc, 0x3e4, 
    0x3, 0x2, 0x2, 0x2, 0xce, 0x3f5, 0x3, 0x2, 0x2, 0x2, 0xd0, 0x3ff, 0x3, 
    0x2, 0x2, 0x2, 0xd2, 0x401, 0x3, 0x2, 0x2, 0x2, 0xd4, 0x475, 0x3, 0x2, 
    0x2, 0x2, 0xd6, 0x477, 0x3, 0x2, 0x2, 0x2, 0xd8, 0x482, 0x3, 0x2, 0x2, 
    0x2, 0xda, 0x485, 0x3, 0x2, 0x2, 0x2, 0xdc, 0x4c9, 0x3, 0x2, 0x2, 0x2, 
    0xde, 0x4cb, 0x3, 0x2, 0x2, 0x2, 0xe0, 0x4cf, 0x3, 0x2, 0x2, 0x2, 0xe2, 
    0x4d8, 0x3, 0x2, 0x2, 0x2, 0xe4, 0x4da, 0x3, 0x2, 0x2, 0x2, 0xe6, 0x4dc, 
    0x3, 0x2, 0x2, 0x2, 0xe8, 0x4de, 0x3, 0x2, 0x2, 0x2, 0xea, 0x4e0, 0x3, 
    0x2, 0x2, 0x2, 0xec, 0x4e2, 0x3, 0x2, 0x2, 0x2, 0xee, 0x4e6, 0x3, 0x2, 
    0x2, 0x2, 0xf0, 0x4e8, 0x3, 0x2, 0x2, 0x2, 0xf2, 0x4f3, 0x3, 0x2, 0x2, 
    0x2, 0xf4, 0xf5, 0x5, 0x4, 0x3, 0x2, 0xf5, 0x3, 0x3, 0x2, 0x2, 0x2, 
    0xf6, 0xfb, 0x5, 0x6, 0x4, 0x2, 0xf7, 0xfc, 0x5, 0xc, 0x7, 0x2, 0xf8, 
    0xfc, 0x5, 0x12, 0xa, 0x2, 0xf9, 0xfc, 0x5, 0x14, 0xb, 0x2, 0xfa, 0xfc, 
    0x5, 0x16, 0xc, 0x2, 0xfb, 0xf7, 0x3, 0x2, 0x2, 0x2, 0xfb, 0xf8, 0x3, 
    0x2, 0x2, 0x2, 0xfb, 0xf9, 0x3, 0x2, 0x2, 0x2, 0xfb, 0xfa, 0x3, 0x2, 
    0x2, 0x2, 0xfc, 0x5, 0x3, 0x2, 0x2, 0x2, 0xfd, 0xff, 0x5, 0x8, 0x5, 
    0x2, 0xfe, 0xfd, 0x3, 0x2, 0x2, 0x2, 0xfe, 0xff, 0x3, 0x2, 0x2, 0x2, 
    0xff, 0x103, 0x3, 0x2, 0x2, 0x2, 0x100, 0x102, 0x5, 0xa, 0x6, 0x2, 0x101, 
    0x100, 0x3, 0x2, 0x2, 0x2, 0x102, 0x105, 0x3, 0x2, 0x2, 0x2, 0x103, 
    0x101, 0x3, 0x2, 0x2, 0x2, 0x103, 0x104, 0x3, 0x2, 0x2, 0x2, 0x104, 
    0x7, 0x3, 0x2, 0x2, 0x2, 0x105, 0x103, 0x3, 0x2, 0x2, 0x2, 0x106, 0x107, 
    0x7, 0x20, 0x2, 0x2, 0x107, 0x108, 0x7, 0x4f, 0x2, 0x2, 0x108, 0x9, 
    0x3, 0x2, 0x2, 0x2, 0x109, 0x10a, 0x7, 0x21, 0x2, 0x2, 0x10a, 0x10b, 
    0x7, 0x50, 0x2, 0x2, 0x10b, 0x10c, 0x7, 0x4f, 0x2, 0x2, 0x10c, 0xb, 
    0x3, 0x2, 0x2, 0x2, 0x10d, 0x111, 0x5, 0x10, 0x9, 0x2, 0x10e, 0x110, 
    0x5, 0x18, 0xd, 0x2, 0x10f, 0x10e, 0x3, 0x2, 0x2, 0x2, 0x110, 0x113, 
    0x3, 0x2, 0x2, 0x2, 0x111, 0x10f, 0x3, 0x2, 0x2, 0x2, 0x111, 0x112, 
    0x3, 0x2, 0x2, 0x2, 0x112, 0x114, 0x3, 0x2, 0x2, 0x2, 0x113, 0x111, 
    0x3, 0x2, 0x2, 0x2, 0x114, 0x115, 0x5, 0x20, 0x11, 0x2, 0x115, 0x116, 
    0x5, 0x22, 0x12, 0x2, 0x116, 0x117, 0x5, 0x36, 0x1c, 0x2, 0x117, 0xd, 
    0x3, 0x2, 0x2, 0x2, 0x118, 0x119, 0x5, 0x10, 0x9, 0x2, 0x119, 0x11a, 
    0x5, 0x20, 0x11, 0x2, 0x11a, 0x11b, 0x5, 0x22, 0x12, 0x2, 0x11b, 0xf, 
    0x3, 0x2, 0x2, 0x2, 0x11c, 0x11e, 0x7, 0x24, 0x2, 0x2, 0x11d, 0x11f, 
    0x9, 0x2, 0x2, 0x2, 0x11e, 0x11d, 0x3, 0x2, 0x2, 0x2, 0x11e, 0x11f, 
    0x3, 0x2, 0x2, 0x2, 0x11f, 0x12c, 0x3, 0x2, 0x2, 0x2, 0x120, 0x128, 
    0x5, 0xba, 0x5e, 0x2, 0x121, 0x122, 0x7, 0x76, 0x2, 0x2, 0x122, 0x123, 
    0x5, 0xbe, 0x60, 0x2, 0x123, 0x124, 0x7, 0x3b, 0x2, 0x2, 0x124, 0x125, 
    0x5, 0xba, 0x5e, 0x2, 0x125, 0x126, 0x7, 0x77, 0x2, 0x2, 0x126, 0x128, 
    0x3, 0x2, 0x2, 0x2, 0x127, 0x120, 0x3, 0x2, 0x2, 0x2, 0x127, 0x121, 
    0x3, 0x2, 0x2, 0x2, 0x128, 0x129, 0x3, 0x2, 0x2, 0x2, 0x129, 0x127, 
    0x3, 0x2, 0x2, 0x2, 0x129, 0x12a, 0x3, 0x2, 0x2, 0x2, 0x12a, 0x12d, 
    0x3, 0x2, 0x2, 0x2, 0x12b, 0x12d, 0x7, 0x6f, 0x2, 0x2, 0x12c, 0x127, 
    0x3, 0x2, 0x2, 0x2, 0x12c, 0x12b, 0x3, 0x2, 0x2, 0x2, 0x12d, 0x11, 0x3, 
    0x2, 0x2, 0x2, 0x12e, 0x12f, 0x7, 0x27, 0x2, 0x2, 0x12f, 0x133, 0x5, 
    0x80, 0x41, 0x2, 0x130, 0x132, 0x5, 0x18, 0xd, 0x2, 0x131, 0x130, 0x3, 
    0x2, 0x2, 0x2, 0x132, 0x135, 0x3, 0x2, 0x2, 0x2, 0x133, 0x131, 0x3, 
    0x2, 0x2, 0x2, 0x133, 0x134, 0x3, 0x2, 0x2, 0x2, 0x134, 0x136, 0x3, 
    0x2, 0x2, 0x2, 0x135, 0x133, 0x3, 0x2, 0x2, 0x2, 0x136, 0x137, 0x5, 
    0x20, 0x11, 0x2, 0x137, 0x138, 0x5, 0x22, 0x12, 0x2, 0x138, 0x13, 0x3, 
    0x2, 0x2, 0x2, 0x139, 0x140, 0x7, 0x28, 0x2, 0x2, 0x13a, 0x13c, 0x5, 
    0xb8, 0x5d, 0x2, 0x13b, 0x13a, 0x3, 0x2, 0x2, 0x2, 0x13c, 0x13d, 0x3, 
    0x2, 0x2, 0x2, 0x13d, 0x13b, 0x3, 0x2, 0x2, 0x2, 0x13d, 0x13e, 0x3, 
    0x2, 0x2, 0x2, 0x13e, 0x141, 0x3, 0x2, 0x2, 0x2, 0x13f, 0x141, 0x7, 
    0x6f, 0x2, 0x2, 0x140, 0x13b, 0x3, 0x2, 0x2, 0x2, 0x140, 0x13f, 0x3, 
    0x2, 0x2, 0x2, 0x141, 0x145, 0x3, 0x2, 0x2, 0x2, 0x142, 0x144, 0x5, 
    0x18, 0xd, 0x2, 0x143, 0x142, 0x3, 0x2, 0x2, 0x2, 0x144, 0x147, 0x3, 
    0x2, 0x2, 0x2, 0x145, 0x143, 0x3, 0x2, 0x2, 0x2, 0x145, 0x146, 0x3, 
    0x2, 0x2, 0x2, 0x146, 0x149, 0x3, 0x2, 0x2, 0x2, 0x147, 0x145, 0x3, 
    0x2, 0x2, 0x2, 0x148, 0x14a, 0x5, 0x20, 0x11, 0x2, 0x149, 0x148, 0x3, 
    0x2, 0x2, 0x2, 0x149, 0x14a, 0x3, 0x2, 0x2, 0x2, 0x14a, 0x14b, 0x3, 
    0x2, 0x2, 0x2, 0x14b, 0x14c, 0x5, 0x22, 0x12, 0x2, 0x14c, 0x15, 0x3, 
    0x2, 0x2, 0x2, 0x14d, 0x151, 0x7, 0x29, 0x2, 0x2, 0x14e, 0x150, 0x5, 
    0x18, 0xd, 0x2, 0x14f, 0x14e, 0x3, 0x2, 0x2, 0x2, 0x150, 0x153, 0x3, 
    0x2, 0x2, 0x2, 0x151, 0x14f, 0x3, 0x2, 0x2, 0x2, 0x151, 0x152, 0x3, 
    0x2, 0x2, 0x2, 0x152, 0x154, 0x3, 0x2, 0x2, 0x2, 0x153, 0x151, 0x3, 
    0x2, 0x2, 0x2, 0x154, 0x155, 0x5, 0x20, 0x11, 0x2, 0x155, 0x17, 0x3, 
    0x2, 0x2, 0x2, 0x156, 0x159, 0x7, 0x2a, 0x2, 0x2, 0x157, 0x15a, 0x5, 
    0x1a, 0xe, 0x2, 0x158, 0x15a, 0x5, 0x1c, 0xf, 0x2, 0x159, 0x157, 0x3, 
    0x2, 0x2, 0x2, 0x159, 0x158, 0x3, 0x2, 0x2, 0x2, 0x15a, 0x19, 0x3, 0x2, 
    0x2, 0x2, 0x15b, 0x15c, 0x5, 0x1e, 0x10, 0x2, 0x15c, 0x1b, 0x3, 0x2, 
    0x2, 0x2, 0x15d, 0x15e, 0x7, 0x2b, 0x2, 0x2, 0x15e, 0x15f, 0x5, 0x1e, 
    0x10, 0x2, 0x15f, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x160, 0x161, 0x5, 0xee, 
    0x78, 0x2, 0x161, 0x1f, 0x3, 0x2, 0x2, 0x2, 0x162, 0x164, 0x7, 0x2c, 
    0x2, 0x2, 0x163, 0x162, 0x3, 0x2, 0x2, 0x2, 0x163, 0x164, 0x3, 0x2, 
    0x2, 0x2, 0x164, 0x165, 0x3, 0x2, 0x2, 0x2, 0x165, 0x166, 0x5, 0x64, 
    0x33, 0x2, 0x166, 0x21, 0x3, 0x2, 0x2, 0x2, 0x167, 0x169, 0x5, 0x24, 
    0x13, 0x2, 0x168, 0x167, 0x3, 0x2, 0x2, 0x2, 0x168, 0x169, 0x3, 0x2, 
    0x2, 0x2, 0x169, 0x16b, 0x3, 0x2, 0x2, 0x2, 0x16a, 0x16c, 0x5, 0x28, 
    0x15, 0x2, 0x16b, 0x16a, 0x3, 0x2, 0x2, 0x2, 0x16b, 0x16c, 0x3, 0x2, 
    0x2, 0x2, 0x16c, 0x16e, 0x3, 0x2, 0x2, 0x2, 0x16d, 0x16f, 0x5, 0x2c, 
    0x17, 0x2, 0x16e, 0x16d, 0x3, 0x2, 0x2, 0x2, 0x16e, 0x16f, 0x3, 0x2, 
    0x2, 0x2, 0x16f, 0x171, 0x3, 0x2, 0x2, 0x2, 0x170, 0x172, 0x5, 0x30, 
    0x19, 0x2, 0x171, 0x170, 0x3, 0x2, 0x2, 0x2, 0x171, 0x172, 0x3, 0x2, 
    0x2, 0x2, 0x172, 0x23, 0x3, 0x2, 0x2, 0x2, 0x173, 0x174, 0x7, 0x2e, 
    0x2, 0x2, 0x174, 0x176, 0x7, 0x2f, 0x2, 0x2, 0x175, 0x177, 0x5, 0x26, 
    0x14, 0x2, 0x176, 0x175, 0x3, 0x2, 0x2, 0x2, 0x177, 0x178, 0x3, 0x2, 
    0x2, 0x2, 0x178, 0x176, 0x3, 0x2, 0x2, 0x2, 0x178, 0x179, 0x3, 0x2, 
    0x2, 0x2, 0x179, 0x25, 0x3, 0x2, 0x2, 0x2, 0x17a, 0x186, 0x5, 0xd4, 
    0x6b, 0x2, 0x17b, 0x186, 0x5, 0x7a, 0x3e, 0x2, 0x17c, 0x17d, 0x7, 0x76, 
    0x2, 0x2, 0x17d, 0x180, 0x5, 0xbe, 0x60, 0x2, 0x17e, 0x17f, 0x7, 0x3b, 
    0x2, 0x2, 0x17f, 0x181, 0x5, 0xba, 0x5e, 0x2, 0x180, 0x17e, 0x3, 0x2, 
    0x2, 0x2, 0x180, 0x181, 0x3, 0x2, 0x2, 0x2, 0x181, 0x182, 0x3, 0x2, 
    0x2, 0x2, 0x182, 0x183, 0x7, 0x77, 0x2, 0x2, 0x183, 0x186, 0x3, 0x2, 
    0x2, 0x2, 0x184, 0x186, 0x5, 0xba, 0x5e, 0x2, 0x185, 0x17a, 0x3, 0x2, 
    0x2, 0x2, 0x185, 0x17b, 0x3, 0x2, 0x2, 0x2, 0x185, 0x17c, 0x3, 0x2, 
    0x2, 0x2, 0x185, 0x184, 0x3, 0x2, 0x2, 0x2, 0x186, 0x27, 0x3, 0x2, 0x2, 
    0x2, 0x187, 0x189, 0x7, 0x13, 0x2, 0x2, 0x188, 0x18a, 0x5, 0x2a, 0x16, 
    0x2, 0x189, 0x188, 0x3, 0x2, 0x2, 0x2, 0x18a, 0x18b, 0x3, 0x2, 0x2, 
    0x2, 0x18b, 0x189, 0x3, 0x2, 0x2, 0x2, 0x18b, 0x18c, 0x3, 0x2, 0x2, 
    0x2, 0x18c, 0x29, 0x3, 0x2, 0x2, 0x2, 0x18d, 0x18e, 0x5, 0x78, 0x3d, 
    0x2, 0x18e, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x18f, 0x190, 0x7, 0x2d, 0x2, 
    0x2, 0x190, 0x192, 0x7, 0x2f, 0x2, 0x2, 0x191, 0x193, 0x5, 0x2e, 0x18, 
    0x2, 0x192, 0x191, 0x3, 0x2, 0x2, 0x2, 0x193, 0x194, 0x3, 0x2, 0x2, 
    0x2, 0x194, 0x192, 0x3, 0x2, 0x2, 0x2, 0x194, 0x195, 0x3, 0x2, 0x2, 
    0x2, 0x195, 0x2d, 0x3, 0x2, 0x2, 0x2, 0x196, 0x197, 0x9, 0x3, 0x2, 0x2, 
    0x197, 0x19d, 0x5, 0xd2, 0x6a, 0x2, 0x198, 0x19b, 0x5, 0x78, 0x3d, 0x2, 
    0x199, 0x19b, 0x5, 0xba, 0x5e, 0x2, 0x19a, 0x198, 0x3, 0x2, 0x2, 0x2, 
    0x19a, 0x199, 0x3, 0x2, 0x2, 0x2, 0x19b, 0x19d, 0x3, 0x2, 0x2, 0x2, 
    0x19c, 0x196, 0x3, 0x2, 0x2, 0x2, 0x19c, 0x19a, 0x3, 0x2, 0x2, 0x2, 
    0x19d, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x19e, 0x1a0, 0x5, 0x32, 0x1a, 0x2, 
    0x19f, 0x1a1, 0x5, 0x34, 0x1b, 0x2, 0x1a0, 0x19f, 0x3, 0x2, 0x2, 0x2, 
    0x1a0, 0x1a1, 0x3, 0x2, 0x2, 0x2, 0x1a1, 0x1a7, 0x3, 0x2, 0x2, 0x2, 
    0x1a2, 0x1a4, 0x5, 0x34, 0x1b, 0x2, 0x1a3, 0x1a5, 0x5, 0x32, 0x1a, 0x2, 
    0x1a4, 0x1a3, 0x3, 0x2, 0x2, 0x2, 0x1a4, 0x1a5, 0x3, 0x2, 0x2, 0x2, 
    0x1a5, 0x1a7, 0x3, 0x2, 0x2, 0x2, 0x1a6, 0x19e, 0x3, 0x2, 0x2, 0x2, 
    0x1a6, 0x1a2, 0x3, 0x2, 0x2, 0x2, 0x1a7, 0x31, 0x3, 0x2, 0x2, 0x2, 0x1a8, 
    0x1a9, 0x7, 0x32, 0x2, 0x2, 0x1a9, 0x1aa, 0x7, 0x55, 0x2, 0x2, 0x1aa, 
    0x33, 0x3, 0x2, 0x2, 0x2, 0x1ab, 0x1ac, 0x7, 0x33, 0x2, 0x2, 0x1ac, 
    0x1ad, 0x7, 0x55, 0x2, 0x2, 0x1ad, 0x35, 0x3, 0x2, 0x2, 0x2, 0x1ae, 
    0x1b2, 0x7, 0x34, 0x2, 0x2, 0x1af, 0x1b1, 0x5, 0xba, 0x5e, 0x2, 0x1b0, 
    0x1af, 0x3, 0x2, 0x2, 0x2, 0x1b1, 0x1b4, 0x3, 0x2, 0x2, 0x2, 0x1b2, 
    0x1b0, 0x3, 0x2, 0x2, 0x2, 0x1b2, 0x1b3, 0x3, 0x2, 0x2, 0x2, 0x1b3, 
    0x1b5, 0x3, 0x2, 0x2, 0x2, 0x1b4, 0x1b2, 0x3, 0x2, 0x2, 0x2, 0x1b5, 
    0x1c8, 0x7, 0x69, 0x2, 0x2, 0x1b6, 0x1b8, 0x7, 0x76, 0x2, 0x2, 0x1b7, 
    0x1b9, 0x5, 0x38, 0x1d, 0x2, 0x1b8, 0x1b7, 0x3, 0x2, 0x2, 0x2, 0x1b9, 
    0x1ba, 0x3, 0x2, 0x2, 0x2, 0x1ba, 0x1b8, 0x3, 0x2, 0x2, 0x2, 0x1ba, 
    0x1bb, 0x3, 0x2, 0x2, 0x2, 0x1bb, 0x1bc, 0x3, 0x2, 0x2, 0x2, 0x1bc, 
    0x1bd, 0x7, 0x77, 0x2, 0x2, 0x1bd, 0x1c7, 0x3, 0x2, 0x2, 0x2, 0x1be, 
    0x1c2, 0x7, 0x76, 0x2, 0x2, 0x1bf, 0x1c1, 0x7, 0x62, 0x2, 0x2, 0x1c0, 
    0x1bf, 0x3, 0x2, 0x2, 0x2, 0x1c1, 0x1c4, 0x3, 0x2, 0x2, 0x2, 0x1c2, 
    0x1c0, 0x3, 0x2, 0x2, 0x2, 0x1c2, 0x1c3, 0x3, 0x2, 0x2, 0x2, 0x1c3, 
    0x1c5, 0x3, 0x2, 0x2, 0x2, 0x1c4, 0x1c2, 0x3, 0x2, 0x2, 0x2, 0x1c5, 
    0x1c7, 0x7, 0x77, 0x2, 0x2, 0x1c6, 0x1b6, 0x3, 0x2, 0x2, 0x2, 0x1c6, 
    0x1be, 0x3, 0x2, 0x2, 0x2, 0x1c7, 0x1ca, 0x3, 0x2, 0x2, 0x2, 0x1c8, 
    0x1c6, 0x3, 0x2, 0x2, 0x2, 0x1c8, 0x1c9, 0x3, 0x2, 0x2, 0x2, 0x1c9, 
    0x1cb, 0x3, 0x2, 0x2, 0x2, 0x1ca, 0x1c8, 0x3, 0x2, 0x2, 0x2, 0x1cb, 
    0x1cd, 0x7, 0x6a, 0x2, 0x2, 0x1cc, 0x1ae, 0x3, 0x2, 0x2, 0x2, 0x1cc, 
    0x1cd, 0x3, 0x2, 0x2, 0x2, 0x1cd, 0x37, 0x3, 0x2, 0x2, 0x2, 0x1ce, 0x1d4, 
    0x5, 0xee, 0x78, 0x2, 0x1cf, 0x1d4, 0x5, 0xe0, 0x71, 0x2, 0x1d0, 0x1d4, 
    0x5, 0xe2, 0x72, 0x2, 0x1d1, 0x1d4, 0x5, 0xea, 0x76, 0x2, 0x1d2, 0x1d4, 
    0x7, 0x7f, 0x2, 0x2, 0x1d3, 0x1ce, 0x3, 0x2, 0x2, 0x2, 0x1d3, 0x1cf, 
    0x3, 0x2, 0x2, 0x2, 0x1d3, 0x1d0, 0x3, 0x2, 0x2, 0x2, 0x1d3, 0x1d1, 
    0x3, 0x2, 0x2, 0x2, 0x1d3, 0x1d2, 0x3, 0x2, 0x2, 0x2, 0x1d4, 0x39, 0x3, 
    0x2, 0x2, 0x2, 0x1d5, 0x1d6, 0x5, 0x3c, 0x1f, 0x2, 0x1d6, 0x3b, 0x3, 
    0x2, 0x2, 0x2, 0x1d7, 0x1d8, 0x5, 0x6, 0x4, 0x2, 0x1d8, 0x1db, 0x5, 
    0x3e, 0x20, 0x2, 0x1d9, 0x1da, 0x7, 0x6b, 0x2, 0x2, 0x1da, 0x1dc, 0x5, 
    0x3c, 0x1f, 0x2, 0x1db, 0x1d9, 0x3, 0x2, 0x2, 0x2, 0x1db, 0x1dc, 0x3, 
    0x2, 0x2, 0x2, 0x1dc, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x1dd, 0x1e7, 0x3, 0x2, 
    0x2, 0x2, 0x1de, 0x1e7, 0x5, 0x40, 0x21, 0x2, 0x1df, 0x1e7, 0x5, 0x42, 
    0x22, 0x2, 0x1e0, 0x1e7, 0x5, 0x44, 0x23, 0x2, 0x1e1, 0x1e7, 0x5, 0x46, 
    0x24, 0x2, 0x1e2, 0x1e7, 0x5, 0x48, 0x25, 0x2, 0x1e3, 0x1e7, 0x5, 0x4a, 
    0x26, 0x2, 0x1e4, 0x1e7, 0x5, 0x4c, 0x27, 0x2, 0x1e5, 0x1e7, 0x5, 0x4e, 
    0x28, 0x2, 0x1e6, 0x1dd, 0x3, 0x2, 0x2, 0x2, 0x1e6, 0x1de, 0x3, 0x2, 
    0x2, 0x2, 0x1e6, 0x1df, 0x3, 0x2, 0x2, 0x2, 0x1e6, 0x1e0, 0x3, 0x2, 
    0x2, 0x2, 0x1e6, 0x1e1, 0x3, 0x2, 0x2, 0x2, 0x1e6, 0x1e2, 0x3, 0x2, 
    0x2, 0x2, 0x1e6, 0x1e3, 0x3, 0x2, 0x2, 0x2, 0x1e6, 0x1e4, 0x3, 0x2, 
    0x2, 0x2, 0x1e6, 0x1e5, 0x3, 0x2, 0x2, 0x2, 0x1e7, 0x3f, 0x3, 0x2, 0x2, 
    0x2, 0x1e8, 0x1e9, 0x7, 0x8, 0x2, 0x2, 0x1e9, 0x1ec, 0x5, 0xee, 0x78, 
    0x2, 0x1ea, 0x1eb, 0x7, 0x7, 0x2, 0x2, 0x1eb, 0x1ed, 0x5, 0x56, 0x2c, 
    0x2, 0x1ec, 0x1ea, 0x3, 0x2, 0x2, 0x2, 0x1ec, 0x1ed, 0x3, 0x2, 0x2, 
    0x2, 0x1ed, 0x41, 0x3, 0x2, 0x2, 0x2, 0x1ee, 0x1f0, 0x7, 0x9, 0x2, 0x2, 
    0x1ef, 0x1f1, 0x7, 0xb, 0x2, 0x2, 0x1f0, 0x1ef, 0x3, 0x2, 0x2, 0x2, 
    0x1f0, 0x1f1, 0x3, 0x2, 0x2, 0x2, 0x1f1, 0x1f2, 0x3, 0x2, 0x2, 0x2, 
    0x1f2, 0x1f3, 0x5, 0x58, 0x2d, 0x2, 0x1f3, 0x43, 0x3, 0x2, 0x2, 0x2, 
    0x1f4, 0x1f6, 0x7, 0xc, 0x2, 0x2, 0x1f5, 0x1f7, 0x7, 0xb, 0x2, 0x2, 
    0x1f6, 0x1f5, 0x3, 0x2, 0x2, 0x2, 0x1f6, 0x1f7, 0x3, 0x2, 0x2, 0x2, 
    0x1f7, 0x1f8, 0x3, 0x2, 0x2, 0x2, 0x1f8, 0x1f9, 0x5, 0x58, 0x2d, 0x2, 
    0x1f9, 0x45, 0x3, 0x2, 0x2, 0x2, 0x1fa, 0x1fc, 0x7, 0xa, 0x2, 0x2, 0x1fb, 
    0x1fd, 0x7, 0xb, 0x2, 0x2, 0x1fc, 0x1fb, 0x3, 0x2, 0x2, 0x2, 0x1fc, 
    0x1fd, 0x3, 0x2, 0x2, 0x2, 0x1fd, 0x1fe, 0x3, 0x2, 0x2, 0x2, 0x1fe, 
    0x1ff, 0x5, 0x56, 0x2c, 0x2, 0x1ff, 0x47, 0x3, 0x2, 0x2, 0x2, 0x200, 
    0x201, 0x7, 0x6, 0x2, 0x2, 0x201, 0x202, 0x7, 0x70, 0x2, 0x2, 0x202, 
    0x203, 0x7, 0x3, 0x2, 0x2, 0x203, 0x204, 0x5, 0x5c, 0x2f, 0x2, 0x204, 
    0x49, 0x3, 0x2, 0x2, 0x2, 0x205, 0x206, 0x7, 0x5, 0x2, 0x2, 0x206, 0x207, 
    0x7, 0x3, 0x2, 0x2, 0x207, 0x208, 0x5, 0x5c, 0x2f, 0x2, 0x208, 0x4b, 
    0x3, 0x2, 0x2, 0x2, 0x209, 0x20a, 0x7, 0x5, 0x2, 0x2, 0x20a, 0x20b, 
    0x7, 0x2c, 0x2, 0x2, 0x20b, 0x20c, 0x5, 0x5a, 0x2e, 0x2, 0x20c, 0x4d, 
    0x3, 0x2, 0x2, 0x2, 0x20d, 0x20e, 0x7, 0x35, 0x2, 0x2, 0x20e, 0x210, 
    0x5, 0xee, 0x78, 0x2, 0x20f, 0x20d, 0x3, 0x2, 0x2, 0x2, 0x20f, 0x210, 
    0x3, 0x2, 0x2, 0x2, 0x210, 0x216, 0x3, 0x2, 0x2, 0x2, 0x211, 0x213, 
    0x5, 0x50, 0x29, 0x2, 0x212, 0x214, 0x5, 0x52, 0x2a, 0x2, 0x213, 0x212, 
    0x3, 0x2, 0x2, 0x2, 0x213, 0x214, 0x3, 0x2, 0x2, 0x2, 0x214, 0x217, 
    0x3, 0x2, 0x2, 0x2, 0x215, 0x217, 0x5, 0x52, 0x2a, 0x2, 0x216, 0x211, 
    0x3, 0x2, 0x2, 0x2, 0x216, 0x215, 0x3, 0x2, 0x2, 0x2, 0x217, 0x21b, 
    0x3, 0x2, 0x2, 0x2, 0x218, 0x21a, 0x5, 0x54, 0x2b, 0x2, 0x219, 0x218, 
    0x3, 0x2, 0x2, 0x2, 0x21a, 0x21d, 0x3, 0x2, 0x2, 0x2, 0x21b, 0x219, 
    0x3, 0x2, 0x2, 0x2, 0x21b, 0x21c, 0x3, 0x2, 0x2, 0x2, 0x21c, 0x21e, 
    0x3, 0x2, 0x2, 0x2, 0x21d, 0x21b, 0x3, 0x2, 0x2, 0x2, 0x21e, 0x21f, 
    0x7, 0x2c, 0x2, 0x2, 0x21f, 0x220, 0x5, 0x64, 0x33, 0x2, 0x220, 0x4f, 
    0x3, 0x2, 0x2, 0x2, 0x221, 0x222, 0x7, 0x5, 0x2, 0x2, 0x222, 0x223, 
    0x5, 0x5a, 0x2e, 0x2, 0x223, 0x51, 0x3, 0x2, 0x2, 0x2, 0x224, 0x225, 
    0x7, 0x6, 0x2, 0x2, 0x225, 0x226, 0x5, 0x5a, 0x2e, 0x2, 0x226, 0x53, 
    0x3, 0x2, 0x2, 0x2, 0x227, 0x22b, 0x7, 0x1c, 0x2, 0x2, 0x228, 0x22c, 
    0x5, 0xee, 0x78, 0x2, 0x229, 0x22a, 0x7, 0x2b, 0x2, 0x2, 0x22a, 0x22c, 
    0x5, 0xee, 0x78, 0x2, 0x22b, 0x228, 0x3, 0x2, 0x2, 0x2, 0x22b, 0x229, 
    0x3, 0x2, 0x2, 0x2, 0x22c, 0x55, 0x3, 0x2, 0x2, 0x2, 0x22d, 0x230, 0x7, 
    0x37, 0x2, 0x2, 0x22e, 0x230, 0x5, 0xee, 0x78, 0x2, 0x22f, 0x22d, 0x3, 
    0x2, 0x2, 0x2, 0x22f, 0x22e, 0x3, 0x2, 0x2, 0x2, 0x230, 0x57, 0x3, 0x2, 
    0x2, 0x2, 0x231, 0x236, 0x5, 0x56, 0x2c, 0x2, 0x232, 0x236, 0x7, 0xd, 
    0x2, 0x2, 0x233, 0x236, 0x7, 0x2b, 0x2, 0x2, 0x234, 0x236, 0x7, 0xe, 
    0x2, 0x2, 0x235, 0x231, 0x3, 0x2, 0x2, 0x2, 0x235, 0x232, 0x3, 0x2, 
    0x2, 0x2, 0x235, 0x233, 0x3, 0x2, 0x2, 0x2, 0x235, 0x234, 0x3, 0x2, 
    0x2, 0x2, 0x236, 0x59, 0x3, 0x2, 0x2, 0x2, 0x237, 0x238, 0x7, 0x69, 
    0x2, 0x2, 0x238, 0x239, 0x5, 0x5e, 0x30, 0x2, 0x239, 0x23a, 0x7, 0x6a, 
    0x2, 0x2, 0x23a, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x23b, 0x23c, 0x7, 0x69, 
    0x2, 0x2, 0x23c, 0x23d, 0x5, 0x5e, 0x30, 0x2, 0x23d, 0x23e, 0x7, 0x6a, 
    0x2, 0x2, 0x23e, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x23f, 0x241, 0x5, 0x62, 
    0x32, 0x2, 0x240, 0x23f, 0x3, 0x2, 0x2, 0x2, 0x240, 0x241, 0x3, 0x2, 
    0x2, 0x2, 0x241, 0x24b, 0x3, 0x2, 0x2, 0x2, 0x242, 0x244, 0x5, 0x60, 
    0x31, 0x2, 0x243, 0x245, 0x7, 0x6c, 0x2, 0x2, 0x244, 0x243, 0x3, 0x2, 
    0x2, 0x2, 0x244, 0x245, 0x3, 0x2, 0x2, 0x2, 0x245, 0x247, 0x3, 0x2, 
    0x2, 0x2, 0x246, 0x248, 0x5, 0x62, 0x32, 0x2, 0x247, 0x246, 0x3, 0x2, 
    0x2, 0x2, 0x247, 0x248, 0x3, 0x2, 0x2, 0x2, 0x248, 0x24a, 0x3, 0x2, 
    0x2, 0x2, 0x249, 0x242, 0x3, 0x2, 0x2, 0x2, 0x24a, 0x24d, 0x3, 0x2, 
    0x2, 0x2, 0x24b, 0x249, 0x3, 0x2, 0x2, 0x2, 0x24b, 0x24c, 0x3, 0x2, 
    0x2, 0x2, 0x24c, 0x5f, 0x3, 0x2, 0x2, 0x2, 0x24d, 0x24b, 0x3, 0x2, 0x2, 
    0x2, 0x24e, 0x24f, 0x7, 0x37, 0x2, 0x2, 0x24f, 0x250, 0x5, 0xb8, 0x5d, 
    0x2, 0x250, 0x251, 0x7, 0x69, 0x2, 0x2, 0x251, 0x252, 0x5, 0x62, 0x32, 
    0x2, 0x252, 0x253, 0x7, 0x6a, 0x2, 0x2, 0x253, 0x61, 0x3, 0x2, 0x2, 
    0x2, 0x254, 0x259, 0x5, 0x84, 0x43, 0x2, 0x255, 0x257, 0x7, 0x6c, 0x2, 
    0x2, 0x256, 0x258, 0x5, 0x62, 0x32, 0x2, 0x257, 0x256, 0x3, 0x2, 0x2, 
    0x2, 0x257, 0x258, 0x3, 0x2, 0x2, 0x2, 0x258, 0x25a, 0x3, 0x2, 0x2, 
    0x2, 0x259, 0x255, 0x3, 0x2, 0x2, 0x2, 0x259, 0x25a, 0x3, 0x2, 0x2, 
    0x2, 0x25a, 0x63, 0x3, 0x2, 0x2, 0x2, 0x25b, 0x25e, 0x7, 0x69, 0x2, 
    0x2, 0x25c, 0x25f, 0x5, 0xe, 0x8, 0x2, 0x25d, 0x25f, 0x5, 0x66, 0x34, 
    0x2, 0x25e, 0x25c, 0x3, 0x2, 0x2, 0x2, 0x25e, 0x25d, 0x3, 0x2, 0x2, 
    0x2, 0x25f, 0x260, 0x3, 0x2, 0x2, 0x2, 0x260, 0x261, 0x7, 0x6a, 0x2, 
    0x2, 0x261, 0x65, 0x3, 0x2, 0x2, 0x2, 0x262, 0x264, 0x5, 0x68, 0x35, 
    0x2, 0x263, 0x262, 0x3, 0x2, 0x2, 0x2, 0x263, 0x264, 0x3, 0x2, 0x2, 
    0x2, 0x264, 0x26e, 0x3, 0x2, 0x2, 0x2, 0x265, 0x267, 0x5, 0x6a, 0x36, 
    0x2, 0x266, 0x268, 0x7, 0x6c, 0x2, 0x2, 0x267, 0x266, 0x3, 0x2, 0x2, 
    0x2, 0x267, 0x268, 0x3, 0x2, 0x2, 0x2, 0x268, 0x26a, 0x3, 0x2, 0x2, 
    0x2, 0x269, 0x26b, 0x5, 0x68, 0x35, 0x2, 0x26a, 0x269, 0x3, 0x2, 0x2, 
    0x2, 0x26a, 0x26b, 0x3, 0x2, 0x2, 0x2, 0x26b, 0x26d, 0x3, 0x2, 0x2, 
    0x2, 0x26c, 0x265, 0x3, 0x2, 0x2, 0x2, 0x26d, 0x270, 0x3, 0x2, 0x2, 
    0x2, 0x26e, 0x26c, 0x3, 0x2, 0x2, 0x2, 0x26e, 0x26f, 0x3, 0x2, 0x2, 
    0x2, 0x26f, 0x67, 0x3, 0x2, 0x2, 0x2, 0x270, 0x26e, 0x3, 0x2, 0x2, 0x2, 
    0x271, 0x276, 0x5, 0x90, 0x49, 0x2, 0x272, 0x274, 0x7, 0x6c, 0x2, 0x2, 
    0x273, 0x275, 0x5, 0x68, 0x35, 0x2, 0x274, 0x273, 0x3, 0x2, 0x2, 0x2, 
    0x274, 0x275, 0x3, 0x2, 0x2, 0x2, 0x275, 0x277, 0x3, 0x2, 0x2, 0x2, 
    0x276, 0x272, 0x3, 0x2, 0x2, 0x2, 0x276, 0x277, 0x3, 0x2, 0x2, 0x2, 
    0x277, 0x69, 0x3, 0x2, 0x2, 0x2, 0x278, 0x27f, 0x5, 0x74, 0x3b, 0x2, 
    0x279, 0x27f, 0x5, 0x6c, 0x37, 0x2, 0x27a, 0x27f, 0x5, 0x72, 0x3a, 0x2, 
    0x27b, 0x27f, 0x5, 0x6e, 0x38, 0x2, 0x27c, 0x27f, 0x5, 0x70, 0x39, 0x2, 
    0x27d, 0x27f, 0x5, 0x76, 0x3c, 0x2, 0x27e, 0x278, 0x3, 0x2, 0x2, 0x2, 
    0x27e, 0x279, 0x3, 0x2, 0x2, 0x2, 0x27e, 0x27a, 0x3, 0x2, 0x2, 0x2, 
    0x27e, 0x27b, 0x3, 0x2, 0x2, 0x2, 0x27e, 0x27c, 0x3, 0x2, 0x2, 0x2, 
    0x27e, 0x27d, 0x3, 0x2, 0x2, 0x2, 0x27f, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x280, 
    0x281, 0x7, 0x36, 0x2, 0x2, 0x281, 0x282, 0x5, 0x64, 0x33, 0x2, 0x282, 
    0x6d, 0x3, 0x2, 0x2, 0x2, 0x283, 0x284, 0x7, 0x37, 0x2, 0x2, 0x284, 
    0x285, 0x5, 0xb8, 0x5d, 0x2, 0x285, 0x286, 0x5, 0x64, 0x33, 0x2, 0x286, 
    0x6f, 0x3, 0x2, 0x2, 0x2, 0x287, 0x288, 0x7, 0xf, 0x2, 0x2, 0x288, 0x289, 
    0x5, 0xb8, 0x5d, 0x2, 0x289, 0x28a, 0x5, 0x64, 0x33, 0x2, 0x28a, 0x71, 
    0x3, 0x2, 0x2, 0x2, 0x28b, 0x28c, 0x7, 0x10, 0x2, 0x2, 0x28c, 0x28d, 
    0x5, 0x64, 0x33, 0x2, 0x28d, 0x73, 0x3, 0x2, 0x2, 0x2, 0x28e, 0x293, 
    0x5, 0x64, 0x33, 0x2, 0x28f, 0x290, 0x7, 0x38, 0x2, 0x2, 0x290, 0x292, 
    0x5, 0x64, 0x33, 0x2, 0x291, 0x28f, 0x3, 0x2, 0x2, 0x2, 0x292, 0x295, 
    0x3, 0x2, 0x2, 0x2, 0x293, 0x291, 0x3, 0x2, 0x2, 0x2, 0x293, 0x294, 
    0x3, 0x2, 0x2, 0x2, 0x294, 0x75, 0x3, 0x2, 0x2, 0x2, 0x295, 0x293, 0x3, 
    0x2, 0x2, 0x2, 0x296, 0x297, 0x7, 0x39, 0x2, 0x2, 0x297, 0x298, 0x5, 
    0x78, 0x3d, 0x2, 0x298, 0x77, 0x3, 0x2, 0x2, 0x2, 0x299, 0x29d, 0x5, 
    0xd2, 0x6a, 0x2, 0x29a, 0x29d, 0x5, 0xd4, 0x6b, 0x2, 0x29b, 0x29d, 0x5, 
    0x7a, 0x3e, 0x2, 0x29c, 0x299, 0x3, 0x2, 0x2, 0x2, 0x29c, 0x29a, 0x3, 
    0x2, 0x2, 0x2, 0x29c, 0x29b, 0x3, 0x2, 0x2, 0x2, 0x29d, 0x79, 0x3, 0x2, 
    0x2, 0x2, 0x29e, 0x29f, 0x5, 0xee, 0x78, 0x2, 0x29f, 0x2a0, 0x5, 0x7c, 
    0x3f, 0x2, 0x2a0, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x2a1, 0x2a5, 0x7, 0x76, 
    0x2, 0x2, 0x2a2, 0x2a4, 0x7, 0x62, 0x2, 0x2, 0x2a3, 0x2a2, 0x3, 0x2, 
    0x2, 0x2, 0x2a4, 0x2a7, 0x3, 0x2, 0x2, 0x2, 0x2a5, 0x2a3, 0x3, 0x2, 
    0x2, 0x2, 0x2a5, 0x2a6, 0x3, 0x2, 0x2, 0x2, 0x2a6, 0x2a8, 0x3, 0x2, 
    0x2, 0x2, 0x2a7, 0x2a5, 0x3, 0x2, 0x2, 0x2, 0x2a8, 0x2b8, 0x7, 0x77, 
    0x2, 0x2, 0x2a9, 0x2ab, 0x7, 0x76, 0x2, 0x2, 0x2aa, 0x2ac, 0x7, 0x25, 
    0x2, 0x2, 0x2ab, 0x2aa, 0x3, 0x2, 0x2, 0x2, 0x2ab, 0x2ac, 0x3, 0x2, 
    0x2, 0x2, 0x2ac, 0x2ad, 0x3, 0x2, 0x2, 0x2, 0x2ad, 0x2b2, 0x5, 0xbe, 
    0x60, 0x2, 0x2ae, 0x2af, 0x7, 0x70, 0x2, 0x2, 0x2af, 0x2b1, 0x5, 0xbe, 
    0x60, 0x2, 0x2b0, 0x2ae, 0x3, 0x2, 0x2, 0x2, 0x2b1, 0x2b4, 0x3, 0x2, 
    0x2, 0x2, 0x2b2, 0x2b0, 0x3, 0x2, 0x2, 0x2, 0x2b2, 0x2b3, 0x3, 0x2, 
    0x2, 0x2, 0x2b3, 0x2b5, 0x3, 0x2, 0x2, 0x2, 0x2b4, 0x2b2, 0x3, 0x2, 
    0x2, 0x2, 0x2b5, 0x2b6, 0x7, 0x77, 0x2, 0x2, 0x2b6, 0x2b8, 0x3, 0x2, 
    0x2, 0x2, 0x2b7, 0x2a1, 0x3, 0x2, 0x2, 0x2, 0x2b7, 0x2a9, 0x3, 0x2, 
    0x2, 0x2, 0x2b8, 0x7d, 0x3, 0x2, 0x2, 0x2, 0x2b9, 0x2bd, 0x7, 0x76, 
    0x2, 0x2, 0x2ba, 0x2bc, 0x7, 0x62, 0x2, 0x2, 0x2bb, 0x2ba, 0x3, 0x2, 
    0x2, 0x2, 0x2bc, 0x2bf, 0x3, 0x2, 0x2, 0x2, 0x2bd, 0x2bb, 0x3, 0x2, 
    0x2, 0x2, 0x2bd, 0x2be, 0x3, 0x2, 0x2, 0x2, 0x2be, 0x2c0, 0x3, 0x2, 
    0x2, 0x2, 0x2bf, 0x2bd, 0x3, 0x2, 0x2, 0x2, 0x2c0, 0x2cd, 0x7, 0x77, 
    0x2, 0x2, 0x2c1, 0x2c2, 0x7, 0x76, 0x2, 0x2, 0x2c2, 0x2c7, 0x5, 0xbe, 
    0x60, 0x2, 0x2c3, 0x2c4, 0x7, 0x70, 0x2, 0x2, 0x2c4, 0x2c6, 0x5, 0xbe, 
    0x60, 0x2, 0x2c5, 0x2c3, 0x3, 0x2, 0x2, 0x2, 0x2c6, 0x2c9, 0x3, 0x2, 
    0x2, 0x2, 0x2c7, 0x2c5, 0x3, 0x2, 0x2, 0x2, 0x2c7, 0x2c8, 0x3, 0x2, 
    0x2, 0x2, 0x2c8, 0x2ca, 0x3, 0x2, 0x2, 0x2, 0x2c9, 0x2c7, 0x3, 0x2, 
    0x2, 0x2, 0x2ca, 0x2cb, 0x7, 0x77, 0x2, 0x2, 0x2cb, 0x2cd, 0x3, 0x2, 
    0x2, 0x2, 0x2cc, 0x2b9, 0x3, 0x2, 0x2, 0x2, 0x2cc, 0x2c1, 0x3, 0x2, 
    0x2, 0x2, 0x2cd, 0x7f, 0x3, 0x2, 0x2, 0x2, 0x2ce, 0x2d0, 0x7, 0x69, 
    0x2, 0x2, 0x2cf, 0x2d1, 0x5, 0x82, 0x42, 0x2, 0x2d0, 0x2cf, 0x3, 0x2, 
    0x2, 0x2, 0x2d0, 0x2d1, 0x3, 0x2, 0x2, 0x2, 0x2d1, 0x2d2, 0x3, 0x2, 
    0x2, 0x2, 0x2d2, 0x2d3, 0x7, 0x6a, 0x2, 0x2, 0x2d3, 0x81, 0x3, 0x2, 
    0x2, 0x2, 0x2d4, 0x2d9, 0x5, 0x84, 0x43, 0x2, 0x2d5, 0x2d7, 0x7, 0x6c, 
    0x2, 0x2, 0x2d6, 0x2d8, 0x5, 0x82, 0x42, 0x2, 0x2d7, 0x2d6, 0x3, 0x2, 
    0x2, 0x2, 0x2d7, 0x2d8, 0x3, 0x2, 0x2, 0x2, 0x2d8, 0x2da, 0x3, 0x2, 
    0x2, 0x2, 0x2d9, 0x2d5, 0x3, 0x2, 0x2, 0x2, 0x2d9, 0x2da, 0x3, 0x2, 
    0x2, 0x2, 0x2da, 0x83, 0x3, 0x2, 0x2, 0x2, 0x2db, 0x2dc, 0x5, 0xb6, 
    0x5c, 0x2, 0x2dc, 0x2dd, 0x5, 0x86, 0x44, 0x2, 0x2dd, 0x2e2, 0x3, 0x2, 
    0x2, 0x2, 0x2de, 0x2df, 0x5, 0xae, 0x58, 0x2, 0x2df, 0x2e0, 0x5, 0x88, 
    0x45, 0x2, 0x2e0, 0x2e2, 0x3, 0x2, 0x2, 0x2, 0x2e1, 0x2db, 0x3, 0x2, 
    0x2, 0x2, 0x2e1, 0x2de, 0x3, 0x2, 0x2, 0x2, 0x2e2, 0x85, 0x3, 0x2, 0x2, 
    0x2, 0x2e3, 0x2e4, 0x5, 0x8e, 0x48, 0x2, 0x2e4, 0x2ed, 0x5, 0x8a, 0x46, 
    0x2, 0x2e5, 0x2e9, 0x7, 0x6b, 0x2, 0x2, 0x2e6, 0x2e7, 0x5, 0x8e, 0x48, 
    0x2, 0x2e7, 0x2e8, 0x5, 0x8a, 0x46, 0x2, 0x2e8, 0x2ea, 0x3, 0x2, 0x2, 
    0x2, 0x2e9, 0x2e6, 0x3, 0x2, 0x2, 0x2, 0x2e9, 0x2ea, 0x3, 0x2, 0x2, 
    0x2, 0x2ea, 0x2ec, 0x3, 0x2, 0x2, 0x2, 0x2eb, 0x2e5, 0x3, 0x2, 0x2, 
    0x2, 0x2ec, 0x2ef, 0x3, 0x2, 0x2, 0x2, 0x2ed, 0x2eb, 0x3, 0x2, 0x2, 
    0x2, 0x2ed, 0x2ee, 0x3, 0x2, 0x2, 0x2, 0x2ee, 0x87, 0x3, 0x2, 0x2, 0x2, 
    0x2ef, 0x2ed, 0x3, 0x2, 0x2, 0x2, 0x2f0, 0x2f2, 0x5, 0x86, 0x44, 0x2, 
    0x2f1, 0x2f0, 0x3, 0x2, 0x2, 0x2, 0x2f1, 0x2f2, 0x3, 0x2, 0x2, 0x2, 
    0x2f2, 0x89, 0x3, 0x2, 0x2, 0x2, 0x2f3, 0x2f8, 0x5, 0x8c, 0x47, 0x2, 
    0x2f4, 0x2f5, 0x7, 0x70, 0x2, 0x2, 0x2f5, 0x2f7, 0x5, 0x8c, 0x47, 0x2, 
    0x2f6, 0x2f4, 0x3, 0x2, 0x2, 0x2, 0x2f7, 0x2fa, 0x3, 0x2, 0x2, 0x2, 
    0x2f8, 0x2f6, 0x3, 0x2, 0x2, 0x2, 0x2f8, 0x2f9, 0x3, 0x2, 0x2, 0x2, 
    0x2f9, 0x8b, 0x3, 0x2, 0x2, 0x2, 0x2fa, 0x2f8, 0x3, 0x2, 0x2, 0x2, 0x2fb, 
    0x2fc, 0x5, 0xb4, 0x5b, 0x2, 0x2fc, 0x8d, 0x3, 0x2, 0x2, 0x2, 0x2fd, 
    0x300, 0x5, 0xb8, 0x5d, 0x2, 0x2fe, 0x300, 0x7, 0x3a, 0x2, 0x2, 0x2ff, 
    0x2fd, 0x3, 0x2, 0x2, 0x2, 0x2ff, 0x2fe, 0x3, 0x2, 0x2, 0x2, 0x300, 
    0x8f, 0x3, 0x2, 0x2, 0x2, 0x301, 0x302, 0x5, 0xb6, 0x5c, 0x2, 0x302, 
    0x303, 0x5, 0x92, 0x4a, 0x2, 0x303, 0x308, 0x3, 0x2, 0x2, 0x2, 0x304, 
    0x305, 0x5, 0xae, 0x58, 0x2, 0x305, 0x306, 0x5, 0x94, 0x4b, 0x2, 0x306, 
    0x308, 0x3, 0x2, 0x2, 0x2, 0x307, 0x301, 0x3, 0x2, 0x2, 0x2, 0x307, 
    0x304, 0x3, 0x2, 0x2, 0x2, 0x308, 0x91, 0x3, 0x2, 0x2, 0x2, 0x309, 0x30c, 
    0x5, 0x96, 0x4c, 0x2, 0x30a, 0x30c, 0x5, 0x98, 0x4d, 0x2, 0x30b, 0x309, 
    0x3, 0x2, 0x2, 0x2, 0x30b, 0x30a, 0x3, 0x2, 0x2, 0x2, 0x30c, 0x30d, 
    0x3, 0x2, 0x2, 0x2, 0x30d, 0x319, 0x5, 0x8a, 0x46, 0x2, 0x30e, 0x315, 
    0x7, 0x6b, 0x2, 0x2, 0x30f, 0x312, 0x5, 0x96, 0x4c, 0x2, 0x310, 0x312, 
    0x5, 0x98, 0x4d, 0x2, 0x311, 0x30f, 0x3, 0x2, 0x2, 0x2, 0x311, 0x310, 
    0x3, 0x2, 0x2, 0x2, 0x312, 0x313, 0x3, 0x2, 0x2, 0x2, 0x313, 0x314, 
    0x5, 0x8a, 0x46, 0x2, 0x314, 0x316, 0x3, 0x2, 0x2, 0x2, 0x315, 0x311, 
    0x3, 0x2, 0x2, 0x2, 0x315, 0x316, 0x3, 0x2, 0x2, 0x2, 0x316, 0x318, 
    0x3, 0x2, 0x2, 0x2, 0x317, 0x30e, 0x3, 0x2, 0x2, 0x2, 0x318, 0x31b, 
    0x3, 0x2, 0x2, 0x2, 0x319, 0x317, 0x3, 0x2, 0x2, 0x2, 0x319, 0x31a, 
    0x3, 0x2, 0x2, 0x2, 0x31a, 0x93, 0x3, 0x2, 0x2, 0x2, 0x31b, 0x319, 0x3, 
    0x2, 0x2, 0x2, 0x31c, 0x31e, 0x5, 0x86, 0x44, 0x2, 0x31d, 0x31c, 0x3, 
    0x2, 0x2, 0x2, 0x31d, 0x31e, 0x3, 0x2, 0x2, 0x2, 0x31e, 0x95, 0x3, 0x2, 
    0x2, 0x2, 0x31f, 0x320, 0x5, 0x9a, 0x4e, 0x2, 0x320, 0x97, 0x3, 0x2, 
    0x2, 0x2, 0x321, 0x322, 0x5, 0xba, 0x5e, 0x2, 0x322, 0x99, 0x3, 0x2, 
    0x2, 0x2, 0x323, 0x324, 0x5, 0x9c, 0x4f, 0x2, 0x324, 0x9b, 0x3, 0x2, 
    0x2, 0x2, 0x325, 0x32a, 0x5, 0x9e, 0x50, 0x2, 0x326, 0x327, 0x7, 0x66, 
    0x2, 0x2, 0x327, 0x329, 0x5, 0x9e, 0x50, 0x2, 0x328, 0x326, 0x3, 0x2, 
    0x2, 0x2, 0x329, 0x32c, 0x3, 0x2, 0x2, 0x2, 0x32a, 0x328, 0x3, 0x2, 
    0x2, 0x2, 0x32a, 0x32b, 0x3, 0x2, 0x2, 0x2, 0x32b, 0x9d, 0x3, 0x2, 0x2, 
    0x2, 0x32c, 0x32a, 0x3, 0x2, 0x2, 0x2, 0x32d, 0x332, 0x5, 0xa2, 0x52, 
    0x2, 0x32e, 0x32f, 0x7, 0x72, 0x2, 0x2, 0x32f, 0x331, 0x5, 0xa2, 0x52, 
    0x2, 0x330, 0x32e, 0x3, 0x2, 0x2, 0x2, 0x331, 0x334, 0x3, 0x2, 0x2, 
    0x2, 0x332, 0x330, 0x3, 0x2, 0x2, 0x2, 0x332, 0x333, 0x3, 0x2, 0x2, 
    0x2, 0x333, 0x9f, 0x3, 0x2, 0x2, 0x2, 0x334, 0x332, 0x3, 0x2, 0x2, 0x2, 
    0x335, 0x337, 0x5, 0xa6, 0x54, 0x2, 0x336, 0x338, 0x5, 0xa4, 0x53, 0x2, 
    0x337, 0x336, 0x3, 0x2, 0x2, 0x2, 0x337, 0x338, 0x3, 0x2, 0x2, 0x2, 
    0x338, 0xa1, 0x3, 0x2, 0x2, 0x2, 0x339, 0x33d, 0x5, 0xa0, 0x51, 0x2, 
    0x33a, 0x33b, 0x7, 0x7d, 0x2, 0x2, 0x33b, 0x33d, 0x5, 0xa0, 0x51, 0x2, 
    0x33c, 0x339, 0x3, 0x2, 0x2, 0x2, 0x33c, 0x33a, 0x3, 0x2, 0x2, 0x2, 
    0x33d, 0xa3, 0x3, 0x2, 0x2, 0x2, 0x33e, 0x354, 0x7, 0x6f, 0x2, 0x2, 
    0x33f, 0x354, 0x7, 0x7e, 0x2, 0x2, 0x340, 0x354, 0x7, 0x6d, 0x2, 0x2, 
    0x341, 0x351, 0x7, 0x69, 0x2, 0x2, 0x342, 0x34b, 0x5, 0xac, 0x57, 0x2, 
    0x343, 0x348, 0x7, 0x70, 0x2, 0x2, 0x344, 0x349, 0x7, 0x6a, 0x2, 0x2, 
    0x345, 0x346, 0x5, 0xac, 0x57, 0x2, 0x346, 0x347, 0x7, 0x6a, 0x2, 0x2, 
    0x347, 0x349, 0x3, 0x2, 0x2, 0x2, 0x348, 0x344, 0x3, 0x2, 0x2, 0x2, 
    0x348, 0x345, 0x3, 0x2, 0x2, 0x2, 0x349, 0x34c, 0x3, 0x2, 0x2, 0x2, 
    0x34a, 0x34c, 0x7, 0x6a, 0x2, 0x2, 0x34b, 0x343, 0x3, 0x2, 0x2, 0x2, 
    0x34b, 0x34a, 0x3, 0x2, 0x2, 0x2, 0x34c, 0x352, 0x3, 0x2, 0x2, 0x2, 
    0x34d, 0x34e, 0x7, 0x70, 0x2, 0x2, 0x34e, 0x34f, 0x5, 0xac, 0x57, 0x2, 
    0x34f, 0x350, 0x7, 0x6a, 0x2, 0x2, 0x350, 0x352, 0x3, 0x2, 0x2, 0x2, 
    0x351, 0x342, 0x3, 0x2, 0x2, 0x2, 0x351, 0x34d, 0x3, 0x2, 0x2, 0x2, 
    0x352, 0x354, 0x3, 0x2, 0x2, 0x2, 0x353, 0x33e, 0x3, 0x2, 0x2, 0x2, 
    0x353, 0x33f, 0x3, 0x2, 0x2, 0x2, 0x353, 0x340, 0x3, 0x2, 0x2, 0x2, 
    0x353, 0x341, 0x3, 0x2, 0x2, 0x2, 0x354, 0xa5, 0x3, 0x2, 0x2, 0x2, 0x355, 
    0x35e, 0x5, 0xee, 0x78, 0x2, 0x356, 0x35e, 0x7, 0x3a, 0x2, 0x2, 0x357, 
    0x358, 0x7, 0x71, 0x2, 0x2, 0x358, 0x35e, 0x5, 0xa8, 0x55, 0x2, 0x359, 
    0x35a, 0x7, 0x76, 0x2, 0x2, 0x35a, 0x35b, 0x5, 0x9a, 0x4e, 0x2, 0x35b, 
    0x35c, 0x7, 0x77, 0x2, 0x2, 0x35c, 0x35e, 0x3, 0x2, 0x2, 0x2, 0x35d, 
    0x355, 0x3, 0x2, 0x2, 0x2, 0x35d, 0x356, 0x3, 0x2, 0x2, 0x2, 0x35d, 
    0x357, 0x3, 0x2, 0x2, 0x2, 0x35d, 0x359, 0x3, 0x2, 0x2, 0x2, 0x35e, 
    0xa7, 0x3, 0x2, 0x2, 0x2, 0x35f, 0x36d, 0x5, 0xaa, 0x56, 0x2, 0x360, 
    0x369, 0x7, 0x76, 0x2, 0x2, 0x361, 0x366, 0x5, 0xaa, 0x56, 0x2, 0x362, 
    0x363, 0x7, 0x66, 0x2, 0x2, 0x363, 0x365, 0x5, 0xaa, 0x56, 0x2, 0x364, 
    0x362, 0x3, 0x2, 0x2, 0x2, 0x365, 0x368, 0x3, 0x2, 0x2, 0x2, 0x366, 
    0x364, 0x3, 0x2, 0x2, 0x2, 0x366, 0x367, 0x3, 0x2, 0x2, 0x2, 0x367, 
    0x36a, 0x3, 0x2, 0x2, 0x2, 0x368, 0x366, 0x3, 0x2, 0x2, 0x2, 0x369, 
    0x361, 0x3, 0x2, 0x2, 0x2, 0x369, 0x36a, 0x3, 0x2, 0x2, 0x2, 0x36a, 
    0x36b, 0x3, 0x2, 0x2, 0x2, 0x36b, 0x36d, 0x7, 0x77, 0x2, 0x2, 0x36c, 
    0x35f, 0x3, 0x2, 0x2, 0x2, 0x36c, 0x360, 0x3, 0x2, 0x2, 0x2, 0x36d, 
    0xa9, 0x3, 0x2, 0x2, 0x2, 0x36e, 0x376, 0x5, 0xee, 0x78, 0x2, 0x36f, 
    0x376, 0x7, 0x3a, 0x2, 0x2, 0x370, 0x373, 0x7, 0x7d, 0x2, 0x2, 0x371, 
    0x374, 0x5, 0xee, 0x78, 0x2, 0x372, 0x374, 0x7, 0x3a, 0x2, 0x2, 0x373, 
    0x371, 0x3, 0x2, 0x2, 0x2, 0x373, 0x372, 0x3, 0x2, 0x2, 0x2, 0x374, 
    0x376, 0x3, 0x2, 0x2, 0x2, 0x375, 0x36e, 0x3, 0x2, 0x2, 0x2, 0x375, 
    0x36f, 0x3, 0x2, 0x2, 0x2, 0x375, 0x370, 0x3, 0x2, 0x2, 0x2, 0x376, 
    0xab, 0x3, 0x2, 0x2, 0x2, 0x377, 0x378, 0x7, 0x55, 0x2, 0x2, 0x378, 
    0xad, 0x3, 0x2, 0x2, 0x2, 0x379, 0x37c, 0x5, 0xb2, 0x5a, 0x2, 0x37a, 
    0x37c, 0x5, 0xb0, 0x59, 0x2, 0x37b, 0x379, 0x3, 0x2, 0x2, 0x2, 0x37b, 
    0x37a, 0x3, 0x2, 0x2, 0x2, 0x37c, 0xaf, 0x3, 0x2, 0x2, 0x2, 0x37d, 0x37e, 
    0x7, 0x7b, 0x2, 0x2, 0x37e, 0x37f, 0x5, 0x86, 0x44, 0x2, 0x37f, 0x380, 
    0x7, 0x7c, 0x2, 0x2, 0x380, 0xb1, 0x3, 0x2, 0x2, 0x2, 0x381, 0x383, 
    0x7, 0x76, 0x2, 0x2, 0x382, 0x384, 0x5, 0xb4, 0x5b, 0x2, 0x383, 0x382, 
    0x3, 0x2, 0x2, 0x2, 0x384, 0x385, 0x3, 0x2, 0x2, 0x2, 0x385, 0x383, 
    0x3, 0x2, 0x2, 0x2, 0x385, 0x386, 0x3, 0x2, 0x2, 0x2, 0x386, 0x387, 
    0x3, 0x2, 0x2, 0x2, 0x387, 0x388, 0x7, 0x77, 0x2, 0x2, 0x388, 0xb3, 
    0x3, 0x2, 0x2, 0x2, 0x389, 0x38c, 0x5, 0xb6, 0x5c, 0x2, 0x38a, 0x38c, 
    0x5, 0xae, 0x58, 0x2, 0x38b, 0x389, 0x3, 0x2, 0x2, 0x2, 0x38b, 0x38a, 
    0x3, 0x2, 0x2, 0x2, 0x38c, 0xb5, 0x3, 0x2, 0x2, 0x2, 0x38d, 0x390, 0x5, 
    0xba, 0x5e, 0x2, 0x38e, 0x390, 0x5, 0xbc, 0x5f, 0x2, 0x38f, 0x38d, 0x3, 
    0x2, 0x2, 0x2, 0x38f, 0x38e, 0x3, 0x2, 0x2, 0x2, 0x390, 0xb7, 0x3, 0x2, 
    0x2, 0x2, 0x391, 0x394, 0x5, 0xba, 0x5e, 0x2, 0x392, 0x394, 0x5, 0xee, 
    0x78, 0x2, 0x393, 0x391, 0x3, 0x2, 0x2, 0x2, 0x393, 0x392, 0x3, 0x2, 
    0x2, 0x2, 0x394, 0xb9, 0x3, 0x2, 0x2, 0x2, 0x395, 0x396, 0x9, 0x4, 0x2, 
    0x2, 0x396, 0xbb, 0x3, 0x2, 0x2, 0x2, 0x397, 0x3a5, 0x5, 0xee, 0x78, 
    0x2, 0x398, 0x3a5, 0x5, 0xe0, 0x71, 0x2, 0x399, 0x3a5, 0x5, 0xe2, 0x72, 
    0x2, 0x39a, 0x3a5, 0x5, 0xea, 0x76, 0x2, 0x39b, 0x3a5, 0x5, 0xf2, 0x7a, 
    0x2, 0x39c, 0x3a0, 0x7, 0x76, 0x2, 0x2, 0x39d, 0x39f, 0x7, 0x62, 0x2, 
    0x2, 0x39e, 0x39d, 0x3, 0x2, 0x2, 0x2, 0x39f, 0x3a2, 0x3, 0x2, 0x2, 
    0x2, 0x3a0, 0x39e, 0x3, 0x2, 0x2, 0x2, 0x3a0, 0x3a1, 0x3, 0x2, 0x2, 
    0x2, 0x3a1, 0x3a3, 0x3, 0x2, 0x2, 0x2, 0x3a2, 0x3a0, 0x3, 0x2, 0x2, 
    0x2, 0x3a3, 0x3a5, 0x7, 0x77, 0x2, 0x2, 0x3a4, 0x397, 0x3, 0x2, 0x2, 
    0x2, 0x3a4, 0x398, 0x3, 0x2, 0x2, 0x2, 0x3a4, 0x399, 0x3, 0x2, 0x2, 
    0x2, 0x3a4, 0x39a, 0x3, 0x2, 0x2, 0x2, 0x3a4, 0x39b, 0x3, 0x2, 0x2, 
    0x2, 0x3a4, 0x39c, 0x3, 0x2, 0x2, 0x2, 0x3a5, 0xbd, 0x3, 0x2, 0x2, 0x2, 
    0x3a6, 0x3a7, 0x5, 0xc0, 0x61, 0x2, 0x3a7, 0xbf, 0x3, 0x2, 0x2, 0x2, 
    0x3a8, 0x3ad, 0x5, 0xc2, 0x62, 0x2, 0x3a9, 0x3aa, 0x7, 0x67, 0x2, 0x2, 
    0x3aa, 0x3ac, 0x5, 0xc2, 0x62, 0x2, 0x3ab, 0x3a9, 0x3, 0x2, 0x2, 0x2, 
    0x3ac, 0x3af, 0x3, 0x2, 0x2, 0x2, 0x3ad, 0x3ab, 0x3, 0x2, 0x2, 0x2, 
    0x3ad, 0x3ae, 0x3, 0x2, 0x2, 0x2, 0x3ae, 0xc1, 0x3, 0x2, 0x2, 0x2, 0x3af, 
    0x3ad, 0x3, 0x2, 0x2, 0x2, 0x3b0, 0x3b5, 0x5, 0xc4, 0x63, 0x2, 0x3b1, 
    0x3b2, 0x7, 0x65, 0x2, 0x2, 0x3b2, 0x3b4, 0x5, 0xc4, 0x63, 0x2, 0x3b3, 
    0x3b1, 0x3, 0x2, 0x2, 0x2, 0x3b4, 0x3b7, 0x3, 0x2, 0x2, 0x2, 0x3b5, 
    0x3b3, 0x3, 0x2, 0x2, 0x2, 0x3b5, 0x3b6, 0x3, 0x2, 0x2, 0x2, 0x3b6, 
    0xc3, 0x3, 0x2, 0x2, 0x2, 0x3b7, 0x3b5, 0x3, 0x2, 0x2, 0x2, 0x3b8, 0x3b9, 
    0x5, 0xc6, 0x64, 0x2, 0x3b9, 0xc5, 0x3, 0x2, 0x2, 0x2, 0x3ba, 0x3cc, 
    0x5, 0xc8, 0x65, 0x2, 0x3bb, 0x3bc, 0x7, 0x73, 0x2, 0x2, 0x3bc, 0x3cd, 
    0x5, 0xc8, 0x65, 0x2, 0x3bd, 0x3be, 0x7, 0x7a, 0x2, 0x2, 0x3be, 0x3cd, 
    0x5, 0xc8, 0x65, 0x2, 0x3bf, 0x3c0, 0x7, 0x74, 0x2, 0x2, 0x3c0, 0x3cd, 
    0x5, 0xc8, 0x65, 0x2, 0x3c1, 0x3c2, 0x7, 0x75, 0x2, 0x2, 0x3c2, 0x3cd, 
    0x5, 0xc8, 0x65, 0x2, 0x3c3, 0x3c4, 0x7, 0x78, 0x2, 0x2, 0x3c4, 0x3cd, 
    0x5, 0xc8, 0x65, 0x2, 0x3c5, 0x3c6, 0x7, 0x79, 0x2, 0x2, 0x3c6, 0x3cd, 
    0x5, 0xc8, 0x65, 0x2, 0x3c7, 0x3c8, 0x7, 0x22, 0x2, 0x2, 0x3c8, 0x3cd, 
    0x5, 0x7e, 0x40, 0x2, 0x3c9, 0x3ca, 0x7, 0x23, 0x2, 0x2, 0x3ca, 0x3cb, 
    0x7, 0x22, 0x2, 0x2, 0x3cb, 0x3cd, 0x5, 0x7e, 0x40, 0x2, 0x3cc, 0x3bb, 
    0x3, 0x2, 0x2, 0x2, 0x3cc, 0x3bd, 0x3, 0x2, 0x2, 0x2, 0x3cc, 0x3bf, 
    0x3, 0x2, 0x2, 0x2, 0x3cc, 0x3c1, 0x3, 0x2, 0x2, 0x2, 0x3cc, 0x3c3, 
    0x3, 0x2, 0x2, 0x2, 0x3cc, 0x3c5, 0x3, 0x2, 0x2, 0x2, 0x3cc, 0x3c7, 
    0x3, 0x2, 0x2, 0x2, 0x3cc, 0x3c9, 0x3, 0x2, 0x2, 0x2, 0x3cc, 0x3cd, 
    0x3, 0x2, 0x2, 0x2, 0x3cd, 0xc7, 0x3, 0x2, 0x2, 0x2, 0x3ce, 0x3cf, 0x5, 
    0xca, 0x66, 0x2, 0x3cf, 0xc9, 0x3, 0x2, 0x2, 0x2, 0x3d0, 0x3e1, 0x5, 
    0xcc, 0x67, 0x2, 0x3d1, 0x3d2, 0x7, 0x6d, 0x2, 0x2, 0x3d2, 0x3e0, 0x5, 
    0xcc, 0x67, 0x2, 0x3d3, 0x3d4, 0x7, 0x6e, 0x2, 0x2, 0x3d4, 0x3e0, 0x5, 
    0xcc, 0x67, 0x2, 0x3d5, 0x3d8, 0x5, 0xe6, 0x74, 0x2, 0x3d6, 0x3d8, 0x5, 
    0xe8, 0x75, 0x2, 0x3d7, 0x3d5, 0x3, 0x2, 0x2, 0x2, 0x3d7, 0x3d6, 0x3, 
    0x2, 0x2, 0x2, 0x3d8, 0x3dd, 0x3, 0x2, 0x2, 0x2, 0x3d9, 0x3da, 0x7, 
    0x6f, 0x2, 0x2, 0x3da, 0x3de, 0x5, 0xce, 0x68, 0x2, 0x3db, 0x3dc, 0x7, 
    0x72, 0x2, 0x2, 0x3dc, 0x3de, 0x5, 0xce, 0x68, 0x2, 0x3dd, 0x3d9, 0x3, 
    0x2, 0x2, 0x2, 0x3dd, 0x3db, 0x3, 0x2, 0x2, 0x2, 0x3dd, 0x3de, 0x3, 
    0x2, 0x2, 0x2, 0x3de, 0x3e0, 0x3, 0x2, 0x2, 0x2, 0x3df, 0x3d1, 0x3, 
    0x2, 0x2, 0x2, 0x3df, 0x3d3, 0x3, 0x2, 0x2, 0x2, 0x3df, 0x3d7, 0x3, 
    0x2, 0x2, 0x2, 0x3e0, 0x3e3, 0x3, 0x2, 0x2, 0x2, 0x3e1, 0x3df, 0x3, 
    0x2, 0x2, 0x2, 0x3e1, 0x3e2, 0x3, 0x2, 0x2, 0x2, 0x3e2, 0xcb, 0x3, 0x2, 
    0x2, 0x2, 0x3e3, 0x3e1, 0x3, 0x2, 0x2, 0x2, 0x3e4, 0x3eb, 0x5, 0xce, 
    0x68, 0x2, 0x3e5, 0x3e6, 0x7, 0x6f, 0x2, 0x2, 0x3e6, 0x3ea, 0x5, 0xce, 
    0x68, 0x2, 0x3e7, 0x3e8, 0x7, 0x72, 0x2, 0x2, 0x3e8, 0x3ea, 0x5, 0xce, 
    0x68, 0x2, 0x3e9, 0x3e5, 0x3, 0x2, 0x2, 0x2, 0x3e9, 0x3e7, 0x3, 0x2, 
    0x2, 0x2, 0x3ea, 0x3ed, 0x3, 0x2, 0x2, 0x2, 0x3eb, 0x3e9, 0x3, 0x2, 
    0x2, 0x2, 0x3eb, 0x3ec, 0x3, 0x2, 0x2, 0x2, 0x3ec, 0xcd, 0x3, 0x2, 0x2, 
    0x2, 0x3ed, 0x3eb, 0x3, 0x2, 0x2, 0x2, 0x3ee, 0x3ef, 0x7, 0x71, 0x2, 
    0x2, 0x3ef, 0x3f6, 0x5, 0xd0, 0x69, 0x2, 0x3f0, 0x3f1, 0x7, 0x6d, 0x2, 
    0x2, 0x3f1, 0x3f6, 0x5, 0xd0, 0x69, 0x2, 0x3f2, 0x3f3, 0x7, 0x6e, 0x2, 
    0x2, 0x3f3, 0x3f6, 0x5, 0xd0, 0x69, 0x2, 0x3f4, 0x3f6, 0x5, 0xd0, 0x69, 
    0x2, 0x3f5, 0x3ee, 0x3, 0x2, 0x2, 0x2, 0x3f5, 0x3f0, 0x3, 0x2, 0x2, 
    0x2, 0x3f5, 0x3f2, 0x3, 0x2, 0x2, 0x2, 0x3f5, 0x3f4, 0x3, 0x2, 0x2, 
    0x2, 0x3f6, 0xcf, 0x3, 0x2, 0x2, 0x2, 0x3f7, 0x400, 0x5, 0xd2, 0x6a, 
    0x2, 0x3f8, 0x400, 0x5, 0xd4, 0x6b, 0x2, 0x3f9, 0x400, 0x5, 0xde, 0x70, 
    0x2, 0x3fa, 0x400, 0x5, 0xe0, 0x71, 0x2, 0x3fb, 0x400, 0x5, 0xe2, 0x72, 
    0x2, 0x3fc, 0x400, 0x5, 0xea, 0x76, 0x2, 0x3fd, 0x400, 0x5, 0xba, 0x5e, 
    0x2, 0x3fe, 0x400, 0x5, 0xdc, 0x6f, 0x2, 0x3ff, 0x3f7, 0x3, 0x2, 0x2, 
    0x2, 0x3ff, 0x3f8, 0x3, 0x2, 0x2, 0x2, 0x3ff, 0x3f9, 0x3, 0x2, 0x2, 
    0x2, 0x3ff, 0x3fa, 0x3, 0x2, 0x2, 0x2, 0x3ff, 0x3fb, 0x3, 0x2, 0x2, 
    0x2, 0x3ff, 0x3fc, 0x3, 0x2, 0x2, 0x2, 0x3ff, 0x3fd, 0x3, 0x2, 0x2, 
    0x2, 0x3ff, 0x3fe, 0x3, 0x2, 0x2, 0x2, 0x400, 0xd1, 0x3, 0x2, 0x2, 0x2, 
    0x401, 0x402, 0x7, 0x76, 0x2, 0x2, 0x402, 0x403, 0x5, 0xbe, 0x60, 0x2, 
    0x403, 0x404, 0x7, 0x77, 0x2, 0x2, 0x404, 0xd3, 0x3, 0x2, 0x2, 0x2, 
    0x405, 0x406, 0x7, 0x3c, 0x2, 0x2, 0x406, 0x407, 0x7, 0x76, 0x2, 0x2, 
    0x407, 0x408, 0x5, 0xbe, 0x60, 0x2, 0x408, 0x409, 0x7, 0x77, 0x2, 0x2, 
    0x409, 0x476, 0x3, 0x2, 0x2, 0x2, 0x40a, 0x40b, 0x7, 0x3d, 0x2, 0x2, 
    0x40b, 0x40c, 0x7, 0x76, 0x2, 0x2, 0x40c, 0x40d, 0x5, 0xbe, 0x60, 0x2, 
    0x40d, 0x40e, 0x7, 0x77, 0x2, 0x2, 0x40e, 0x476, 0x3, 0x2, 0x2, 0x2, 
    0x40f, 0x410, 0x7, 0x3e, 0x2, 0x2, 0x410, 0x411, 0x7, 0x76, 0x2, 0x2, 
    0x411, 0x412, 0x5, 0xbe, 0x60, 0x2, 0x412, 0x413, 0x7, 0x70, 0x2, 0x2, 
    0x413, 0x414, 0x5, 0xbe, 0x60, 0x2, 0x414, 0x415, 0x7, 0x77, 0x2, 0x2, 
    0x415, 0x476, 0x3, 0x2, 0x2, 0x2, 0x416, 0x417, 0x7, 0x3f, 0x2, 0x2, 
    0x417, 0x418, 0x7, 0x76, 0x2, 0x2, 0x418, 0x419, 0x5, 0xbe, 0x60, 0x2, 
    0x419, 0x41a, 0x7, 0x77, 0x2, 0x2, 0x41a, 0x476, 0x3, 0x2, 0x2, 0x2, 
    0x41b, 0x41c, 0x7, 0x40, 0x2, 0x2, 0x41c, 0x41d, 0x7, 0x76, 0x2, 0x2, 
    0x41d, 0x41e, 0x5, 0xba, 0x5e, 0x2, 0x41e, 0x41f, 0x7, 0x77, 0x2, 0x2, 
    0x41f, 0x476, 0x3, 0x2, 0x2, 0x2, 0x420, 0x421, 0x7, 0x42, 0x2, 0x2, 
    0x421, 0x422, 0x7, 0x76, 0x2, 0x2, 0x422, 0x423, 0x5, 0xbe, 0x60, 0x2, 
    0x423, 0x424, 0x7, 0x77, 0x2, 0x2, 0x424, 0x476, 0x3, 0x2, 0x2, 0x2, 
    0x425, 0x426, 0x7, 0x43, 0x2, 0x2, 0x426, 0x427, 0x7, 0x76, 0x2, 0x2, 
    0x427, 0x428, 0x5, 0xbe, 0x60, 0x2, 0x428, 0x429, 0x7, 0x77, 0x2, 0x2, 
    0x429, 0x476, 0x3, 0x2, 0x2, 0x2, 0x42a, 0x437, 0x7, 0x44, 0x2, 0x2, 
    0x42b, 0x42c, 0x7, 0x76, 0x2, 0x2, 0x42c, 0x42d, 0x5, 0xba, 0x5e, 0x2, 
    0x42d, 0x42e, 0x7, 0x77, 0x2, 0x2, 0x42e, 0x438, 0x3, 0x2, 0x2, 0x2, 
    0x42f, 0x433, 0x7, 0x76, 0x2, 0x2, 0x430, 0x432, 0x7, 0x62, 0x2, 0x2, 
    0x431, 0x430, 0x3, 0x2, 0x2, 0x2, 0x432, 0x435, 0x3, 0x2, 0x2, 0x2, 
    0x433, 0x431, 0x3, 0x2, 0x2, 0x2, 0x433, 0x434, 0x3, 0x2, 0x2, 0x2, 
    0x434, 0x436, 0x3, 0x2, 0x2, 0x2, 0x435, 0x433, 0x3, 0x2, 0x2, 0x2, 
    0x436, 0x438, 0x7, 0x77, 0x2, 0x2, 0x437, 0x42b, 0x3, 0x2, 0x2, 0x2, 
    0x437, 0x42f, 0x3, 0x2, 0x2, 0x2, 0x438, 0x476, 0x3, 0x2, 0x2, 0x2, 
    0x439, 0x43a, 0x7, 0x1d, 0x2, 0x2, 0x43a, 0x476, 0x5, 0x7e, 0x40, 0x2, 
    0x43b, 0x43c, 0x7, 0x1f, 0x2, 0x2, 0x43c, 0x43d, 0x7, 0x76, 0x2, 0x2, 
    0x43d, 0x43e, 0x5, 0xbe, 0x60, 0x2, 0x43e, 0x43f, 0x7, 0x70, 0x2, 0x2, 
    0x43f, 0x440, 0x5, 0xbe, 0x60, 0x2, 0x440, 0x441, 0x7, 0x70, 0x2, 0x2, 
    0x441, 0x442, 0x5, 0xbe, 0x60, 0x2, 0x442, 0x443, 0x7, 0x77, 0x2, 0x2, 
    0x443, 0x476, 0x3, 0x2, 0x2, 0x2, 0x444, 0x445, 0x7, 0x45, 0x2, 0x2, 
    0x445, 0x446, 0x7, 0x76, 0x2, 0x2, 0x446, 0x447, 0x5, 0xbe, 0x60, 0x2, 
    0x447, 0x448, 0x7, 0x70, 0x2, 0x2, 0x448, 0x449, 0x5, 0xbe, 0x60, 0x2, 
    0x449, 0x44a, 0x7, 0x77, 0x2, 0x2, 0x44a, 0x476, 0x3, 0x2, 0x2, 0x2, 
    0x44b, 0x44c, 0x7, 0x46, 0x2, 0x2, 0x44c, 0x44d, 0x7, 0x76, 0x2, 0x2, 
    0x44d, 0x44e, 0x5, 0xbe, 0x60, 0x2, 0x44e, 0x44f, 0x7, 0x70, 0x2, 0x2, 
    0x44f, 0x450, 0x5, 0xbe, 0x60, 0x2, 0x450, 0x451, 0x7, 0x77, 0x2, 0x2, 
    0x451, 0x476, 0x3, 0x2, 0x2, 0x2, 0x452, 0x453, 0x7, 0x41, 0x2, 0x2, 
    0x453, 0x454, 0x7, 0x76, 0x2, 0x2, 0x454, 0x455, 0x5, 0xbe, 0x60, 0x2, 
    0x455, 0x456, 0x7, 0x70, 0x2, 0x2, 0x456, 0x457, 0x5, 0xbe, 0x60, 0x2, 
    0x457, 0x458, 0x7, 0x77, 0x2, 0x2, 0x458, 0x476, 0x3, 0x2, 0x2, 0x2, 
    0x459, 0x45a, 0x7, 0x47, 0x2, 0x2, 0x45a, 0x45b, 0x7, 0x76, 0x2, 0x2, 
    0x45b, 0x45c, 0x5, 0xbe, 0x60, 0x2, 0x45c, 0x45d, 0x7, 0x77, 0x2, 0x2, 
    0x45d, 0x476, 0x3, 0x2, 0x2, 0x2, 0x45e, 0x45f, 0x7, 0x48, 0x2, 0x2, 
    0x45f, 0x460, 0x7, 0x76, 0x2, 0x2, 0x460, 0x461, 0x5, 0xbe, 0x60, 0x2, 
    0x461, 0x462, 0x7, 0x77, 0x2, 0x2, 0x462, 0x476, 0x3, 0x2, 0x2, 0x2, 
    0x463, 0x464, 0x7, 0x49, 0x2, 0x2, 0x464, 0x465, 0x7, 0x76, 0x2, 0x2, 
    0x465, 0x466, 0x5, 0xbe, 0x60, 0x2, 0x466, 0x467, 0x7, 0x77, 0x2, 0x2, 
    0x467, 0x476, 0x3, 0x2, 0x2, 0x2, 0x468, 0x469, 0x7, 0x4a, 0x2, 0x2, 
    0x469, 0x46a, 0x7, 0x76, 0x2, 0x2, 0x46a, 0x46b, 0x5, 0xbe, 0x60, 0x2, 
    0x46b, 0x46c, 0x7, 0x77, 0x2, 0x2, 0x46c, 0x476, 0x3, 0x2, 0x2, 0x2, 
    0x46d, 0x46e, 0x7, 0x4b, 0x2, 0x2, 0x46e, 0x46f, 0x7, 0x76, 0x2, 0x2, 
    0x46f, 0x470, 0x5, 0xbe, 0x60, 0x2, 0x470, 0x471, 0x7, 0x77, 0x2, 0x2, 
    0x471, 0x476, 0x3, 0x2, 0x2, 0x2, 0x472, 0x476, 0x5, 0xd6, 0x6c, 0x2, 
    0x473, 0x476, 0x5, 0xd8, 0x6d, 0x2, 0x474, 0x476, 0x5, 0xda, 0x6e, 0x2, 
    0x475, 0x405, 0x3, 0x2, 0x2, 0x2, 0x475, 0x40a, 0x3, 0x2, 0x2, 0x2, 
    0x475, 0x40f, 0x3, 0x2, 0x2, 0x2, 0x475, 0x416, 0x3, 0x2, 0x2, 0x2, 
    0x475, 0x41b, 0x3, 0x2, 0x2, 0x2, 0x475, 0x420, 0x3, 0x2, 0x2, 0x2, 
    0x475, 0x425, 0x3, 0x2, 0x2, 0x2, 0x475, 0x42a, 0x3, 0x2, 0x2, 0x2, 
    0x475, 0x439, 0x3, 0x2, 0x2, 0x2, 0x475, 0x43b, 0x3, 0x2, 0x2, 0x2, 
    0x475, 0x444, 0x3, 0x2, 0x2, 0x2, 0x475, 0x44b, 0x3, 0x2, 0x2, 0x2, 
    0x475, 0x452, 0x3, 0x2, 0x2, 0x2, 0x475, 0x459, 0x3, 0x2, 0x2, 0x2, 
    0x475, 0x45e, 0x3, 0x2, 0x2, 0x2, 0x475, 0x463, 0x3, 0x2, 0x2, 0x2, 
    0x475, 0x468, 0x3, 0x2, 0x2, 0x2, 0x475, 0x46d, 0x3, 0x2, 0x2, 0x2, 
    0x475, 0x472, 0x3, 0x2, 0x2, 0x2, 0x475, 0x473, 0x3, 0x2, 0x2, 0x2, 
    0x475, 0x474, 0x3, 0x2, 0x2, 0x2, 0x476, 0xd5, 0x3, 0x2, 0x2, 0x2, 0x477, 
    0x478, 0x7, 0x4c, 0x2, 0x2, 0x478, 0x479, 0x7, 0x76, 0x2, 0x2, 0x479, 
    0x47a, 0x5, 0xbe, 0x60, 0x2, 0x47a, 0x47b, 0x7, 0x70, 0x2, 0x2, 0x47b, 
    0x47e, 0x5, 0xbe, 0x60, 0x2, 0x47c, 0x47d, 0x7, 0x70, 0x2, 0x2, 0x47d, 
    0x47f, 0x5, 0xbe, 0x60, 0x2, 0x47e, 0x47c, 0x3, 0x2, 0x2, 0x2, 0x47e, 
    0x47f, 0x3, 0x2, 0x2, 0x2, 0x47f, 0x480, 0x3, 0x2, 0x2, 0x2, 0x480, 
    0x481, 0x7, 0x77, 0x2, 0x2, 0x481, 0xd7, 0x3, 0x2, 0x2, 0x2, 0x482, 
    0x483, 0x7, 0x11, 0x2, 0x2, 0x483, 0x484, 0x5, 0x64, 0x33, 0x2, 0x484, 
    0xd9, 0x3, 0x2, 0x2, 0x2, 0x485, 0x486, 0x7, 0x23, 0x2, 0x2, 0x486, 
    0x487, 0x7, 0x11, 0x2, 0x2, 0x487, 0x488, 0x5, 0x64, 0x33, 0x2, 0x488, 
    0xdb, 0x3, 0x2, 0x2, 0x2, 0x489, 0x48a, 0x7, 0x14, 0x2, 0x2, 0x48a, 
    0x48c, 0x7, 0x76, 0x2, 0x2, 0x48b, 0x48d, 0x7, 0x25, 0x2, 0x2, 0x48c, 
    0x48b, 0x3, 0x2, 0x2, 0x2, 0x48c, 0x48d, 0x3, 0x2, 0x2, 0x2, 0x48d, 
    0x490, 0x3, 0x2, 0x2, 0x2, 0x48e, 0x491, 0x7, 0x6f, 0x2, 0x2, 0x48f, 
    0x491, 0x5, 0xbe, 0x60, 0x2, 0x490, 0x48e, 0x3, 0x2, 0x2, 0x2, 0x490, 
    0x48f, 0x3, 0x2, 0x2, 0x2, 0x491, 0x492, 0x3, 0x2, 0x2, 0x2, 0x492, 
    0x4ca, 0x7, 0x77, 0x2, 0x2, 0x493, 0x494, 0x7, 0x15, 0x2, 0x2, 0x494, 
    0x496, 0x7, 0x76, 0x2, 0x2, 0x495, 0x497, 0x7, 0x25, 0x2, 0x2, 0x496, 
    0x495, 0x3, 0x2, 0x2, 0x2, 0x496, 0x497, 0x3, 0x2, 0x2, 0x2, 0x497, 
    0x498, 0x3, 0x2, 0x2, 0x2, 0x498, 0x499, 0x5, 0xbe, 0x60, 0x2, 0x499, 
    0x49a, 0x7, 0x77, 0x2, 0x2, 0x49a, 0x4ca, 0x3, 0x2, 0x2, 0x2, 0x49b, 
    0x49c, 0x7, 0x16, 0x2, 0x2, 0x49c, 0x49e, 0x7, 0x76, 0x2, 0x2, 0x49d, 
    0x49f, 0x7, 0x25, 0x2, 0x2, 0x49e, 0x49d, 0x3, 0x2, 0x2, 0x2, 0x49e, 
    0x49f, 0x3, 0x2, 0x2, 0x2, 0x49f, 0x4a0, 0x3, 0x2, 0x2, 0x2, 0x4a0, 
    0x4a1, 0x5, 0xbe, 0x60, 0x2, 0x4a1, 0x4a2, 0x7, 0x77, 0x2, 0x2, 0x4a2, 
    0x4ca, 0x3, 0x2, 0x2, 0x2, 0x4a3, 0x4a4, 0x7, 0x17, 0x2, 0x2, 0x4a4, 
    0x4a6, 0x7, 0x76, 0x2, 0x2, 0x4a5, 0x4a7, 0x7, 0x25, 0x2, 0x2, 0x4a6, 
    0x4a5, 0x3, 0x2, 0x2, 0x2, 0x4a6, 0x4a7, 0x3, 0x2, 0x2, 0x2, 0x4a7, 
    0x4a8, 0x3, 0x2, 0x2, 0x2, 0x4a8, 0x4a9, 0x5, 0xbe, 0x60, 0x2, 0x4a9, 
    0x4aa, 0x7, 0x77, 0x2, 0x2, 0x4aa, 0x4ca, 0x3, 0x2, 0x2, 0x2, 0x4ab, 
    0x4ac, 0x7, 0x18, 0x2, 0x2, 0x4ac, 0x4ae, 0x7, 0x76, 0x2, 0x2, 0x4ad, 
    0x4af, 0x7, 0x25, 0x2, 0x2, 0x4ae, 0x4ad, 0x3, 0x2, 0x2, 0x2, 0x4ae, 
    0x4af, 0x3, 0x2, 0x2, 0x2, 0x4af, 0x4b0, 0x3, 0x2, 0x2, 0x2, 0x4b0, 
    0x4b1, 0x5, 0xbe, 0x60, 0x2, 0x4b1, 0x4b2, 0x7, 0x77, 0x2, 0x2, 0x4b2, 
    0x4ca, 0x3, 0x2, 0x2, 0x2, 0x4b3, 0x4b4, 0x7, 0x19, 0x2, 0x2, 0x4b4, 
    0x4b6, 0x7, 0x76, 0x2, 0x2, 0x4b5, 0x4b7, 0x7, 0x25, 0x2, 0x2, 0x4b6, 
    0x4b5, 0x3, 0x2, 0x2, 0x2, 0x4b6, 0x4b7, 0x3, 0x2, 0x2, 0x2, 0x4b7, 
    0x4b8, 0x3, 0x2, 0x2, 0x2, 0x4b8, 0x4b9, 0x5, 0xbe, 0x60, 0x2, 0x4b9, 
    0x4ba, 0x7, 0x77, 0x2, 0x2, 0x4ba, 0x4ca, 0x3, 0x2, 0x2, 0x2, 0x4bb, 
    0x4bc, 0x7, 0x1a, 0x2, 0x2, 0x4bc, 0x4be, 0x7, 0x76, 0x2, 0x2, 0x4bd, 
    0x4bf, 0x7, 0x25, 0x2, 0x2, 0x4be, 0x4bd, 0x3, 0x2, 0x2, 0x2, 0x4be, 
    0x4bf, 0x3, 0x2, 0x2, 0x2, 0x4bf, 0x4c0, 0x3, 0x2, 0x2, 0x2, 0x4c0, 
    0x4c5, 0x5, 0xbe, 0x60, 0x2, 0x4c1, 0x4c2, 0x7, 0x6b, 0x2, 0x2, 0x4c2, 
    0x4c3, 0x7, 0x1b, 0x2, 0x2, 0x4c3, 0x4c4, 0x7, 0x73, 0x2, 0x2, 0x4c4, 
    0x4c6, 0x5, 0xec, 0x77, 0x2, 0x4c5, 0x4c1, 0x3, 0x2, 0x2, 0x2, 0x4c5, 
    0x4c6, 0x3, 0x2, 0x2, 0x2, 0x4c6, 0x4c7, 0x3, 0x2, 0x2, 0x2, 0x4c7, 
    0x4c8, 0x7, 0x77, 0x2, 0x2, 0x4c8, 0x4ca, 0x3, 0x2, 0x2, 0x2, 0x4c9, 
    0x489, 0x3, 0x2, 0x2, 0x2, 0x4c9, 0x493, 0x3, 0x2, 0x2, 0x2, 0x4c9, 
    0x49b, 0x3, 0x2, 0x2, 0x2, 0x4c9, 0x4a3, 0x3, 0x2, 0x2, 0x2, 0x4c9, 
    0x4ab, 0x3, 0x2, 0x2, 0x2, 0x4c9, 0x4b3, 0x3, 0x2, 0x2, 0x2, 0x4c9, 
    0x4bb, 0x3, 0x2, 0x2, 0x2, 0x4ca, 0xdd, 0x3, 0x2, 0x2, 0x2, 0x4cb, 0x4cd, 
    0x5, 0xee, 0x78, 0x2, 0x4cc, 0x4ce, 0x5, 0x7c, 0x3f, 0x2, 0x4cd, 0x4cc, 
    0x3, 0x2, 0x2, 0x2, 0x4cd, 0x4ce, 0x3, 0x2, 0x2, 0x2, 0x4ce, 0xdf, 0x3, 
    0x2, 0x2, 0x2, 0x4cf, 0x4d3, 0x5, 0xec, 0x77, 0x2, 0x4d0, 0x4d4, 0x7, 
    0x54, 0x2, 0x2, 0x4d1, 0x4d2, 0x7, 0x64, 0x2, 0x2, 0x4d2, 0x4d4, 0x5, 
    0xee, 0x78, 0x2, 0x4d3, 0x4d0, 0x3, 0x2, 0x2, 0x2, 0x4d3, 0x4d1, 0x3, 
    0x2, 0x2, 0x2, 0x4d3, 0x4d4, 0x3, 0x2, 0x2, 0x2, 0x4d4, 0xe1, 0x3, 0x2, 
    0x2, 0x2, 0x4d5, 0x4d9, 0x5, 0xe4, 0x73, 0x2, 0x4d6, 0x4d9, 0x5, 0xe6, 
    0x74, 0x2, 0x4d7, 0x4d9, 0x5, 0xe8, 0x75, 0x2, 0x4d8, 0x4d5, 0x3, 0x2, 
    0x2, 0x2, 0x4d8, 0x4d6, 0x3, 0x2, 0x2, 0x2, 0x4d8, 0x4d7, 0x3, 0x2, 
    0x2, 0x2, 0x4d9, 0xe3, 0x3, 0x2, 0x2, 0x2, 0x4da, 0x4db, 0x9, 0x5, 0x2, 
    0x2, 0x4db, 0xe5, 0x3, 0x2, 0x2, 0x2, 0x4dc, 0x4dd, 0x9, 0x6, 0x2, 0x2, 
    0x4dd, 0xe7, 0x3, 0x2, 0x2, 0x2, 0x4de, 0x4df, 0x9, 0x7, 0x2, 0x2, 0x4df, 
    0xe9, 0x3, 0x2, 0x2, 0x2, 0x4e0, 0x4e1, 0x9, 0x8, 0x2, 0x2, 0x4e1, 0xeb, 
    0x3, 0x2, 0x2, 0x2, 0x4e2, 0x4e3, 0x9, 0x9, 0x2, 0x2, 0x4e3, 0xed, 0x3, 
    0x2, 0x2, 0x2, 0x4e4, 0x4e7, 0x7, 0x4f, 0x2, 0x2, 0x4e5, 0x4e7, 0x5, 
    0xf0, 0x79, 0x2, 0x4e6, 0x4e4, 0x3, 0x2, 0x2, 0x2, 0x4e6, 0x4e5, 0x3, 
    0x2, 0x2, 0x2, 0x4e7, 0xef, 0x3, 0x2, 0x2, 0x2, 0x4e8, 0x4e9, 0x9, 0xa, 
    0x2, 0x2, 0x4e9, 0xf1, 0x3, 0x2, 0x2, 0x2, 0x4ea, 0x4f4, 0x7, 0x63, 
    0x2, 0x2, 0x4eb, 0x4ef, 0x7, 0x7b, 0x2, 0x2, 0x4ec, 0x4ee, 0x7, 0x62, 
    0x2, 0x2, 0x4ed, 0x4ec, 0x3, 0x2, 0x2, 0x2, 0x4ee, 0x4f1, 0x3, 0x2, 
    0x2, 0x2, 0x4ef, 0x4ed, 0x3, 0x2, 0x2, 0x2, 0x4ef, 0x4f0, 0x3, 0x2, 
    0x2, 0x2, 0x4f0, 0x4f2, 0x3, 0x2, 0x2, 0x2, 0x4f1, 0x4ef, 0x3, 0x2, 
    0x2, 0x2, 0x4f2, 0x4f4, 0x7, 0x7c, 0x2, 0x2, 0x4f3, 0x4ea, 0x3, 0x2, 
    0x2, 0x2, 0x4f3, 0x4eb, 0x3, 0x2, 0x2, 0x2, 0x4f4, 0xf3, 0x3, 0x2, 0x2, 
    0x2, 0x8e, 0xfb, 0xfe, 0x103, 0x111, 0x11e, 0x127, 0x129, 0x12c, 0x133, 
    0x13d, 0x140, 0x145, 0x149, 0x151, 0x159, 0x163, 0x168, 0x16b, 0x16e, 
    0x171, 0x178, 0x180, 0x185, 0x18b, 0x194, 0x19a, 0x19c, 0x1a0, 0x1a4, 
    0x1a6, 0x1b2, 0x1ba, 0x1c2, 0x1c6, 0x1c8, 0x1cc, 0x1d3, 0x1db, 0x1e6, 
    0x1ec, 0x1f0, 0x1f6, 0x1fc, 0x20f, 0x213, 0x216, 0x21b, 0x22b, 0x22f, 
    0x235, 0x240, 0x244, 0x247, 0x24b, 0x257, 0x259, 0x25e, 0x263, 0x267, 
    0x26a, 0x26e, 0x274, 0x276, 0x27e, 0x293, 0x29c, 0x2a5, 0x2ab, 0x2b2, 
    0x2b7, 0x2bd, 0x2c7, 0x2cc, 0x2d0, 0x2d7, 0x2d9, 0x2e1, 0x2e9, 0x2ed, 
    0x2f1, 0x2f8, 0x2ff, 0x307, 0x30b, 0x311, 0x315, 0x319, 0x31d, 0x32a, 
    0x332, 0x337, 0x33c, 0x348, 0x34b, 0x351, 0x353, 0x35d, 0x366, 0x369, 
    0x36c, 0x373, 0x375, 0x37b, 0x385, 0x38b, 0x38f, 0x393, 0x3a0, 0x3a4, 
    0x3ad, 0x3b5, 0x3cc, 0x3d7, 0x3dd, 0x3df, 0x3e1, 0x3e9, 0x3eb, 0x3f5, 
    0x3ff, 0x433, 0x437, 0x475, 0x47e, 0x48c, 0x490, 0x496, 0x49e, 0x4a6, 
    0x4ae, 0x4b6, 0x4be, 0x4c5, 0x4c9, 0x4cd, 0x4d3, 0x4d8, 0x4e6, 0x4ef, 
    0x4f3, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

Sparql11Parser::Initializer Sparql11Parser::_init;
