grammar Sparql11;

options {
  language  = Cpp;
  output  = AST;
}

@parser::includes
{
   #include "Sparql11Lexer.hpp"
}

@lexer::namespace {	User }
@parser::namespace{	User }

@lexer::traits 
{
	class Sparql11Lexer;
	class Sparql11Parser;

	template<class ImplTraits>
	class UserTraits : public antlr3::CustomTraitsBase<ImplTraits>
	{
	public:
	    //for using the token stream which deleted the tokens, once it is reduced to a rule
		//but it leaves the start and stop tokens. So they can be accessed as usual
		static const bool TOKENS_ACCESSED_FROM_OWNING_RULE = true;
	};

	typedef antlr3::Traits< Sparql11Lexer, Sparql11Parser, UserTraits > Sparql11LexerTraits;
	typedef Sparql11LexerTraits Sparql11ParserTraits;

	/* If you don't want the override it is like this.
	   class TLexer;
	   class TParser;
	   typedef antlr3::Traits< TLexer, TParser > TLexerTraits;
	   typedef TLexerTraits TParserTraits;
	 */
}


/* sparql 1.1 r1 */
// $<Parser

queryUnit
  :
  query
  ;

/* sparql 1.1 r2 */

query
  :
  prologue
  (
    selectQuery
    | constructQuery
    | describeQuery
    | askQuery
  )
  ;

/* sparql 1.1 r3 */

prologue
  :
  baseDecl? prefixDecl*
  ;

/* sparql 1.1 r4 */

baseDecl
  :
  BASE IRI_REF
  ;

/* sparql 1.1 r5 */

prefixDecl
  :
  PREFIX PNAME_NS IRI_REF
  ;

/* sparql 1.1 r6 */

selectQuery
  :
  selectClause datasetClause* whereClause solutionModifier bindingsClause
  ;

/* sparql 1.1 r7 */

subSelect
  :
  selectClause whereClause solutionModifier
  ;

/* sparql 1.1 r8 */

selectClause
  :
  SELECT
  (
    DISTINCT
    | REDUCED
  )?
  (
    (variable
    | (OPEN_BRACE expression AS variable CLOSE_BRACE)
    )+
    | ASTERISK
  )
  ;

/* sparql 1.1 r9 */

constructQuery
  :
  CONSTRUCT constructTemplate datasetClause* whereClause solutionModifier
  ;

/* sparql 1.1 r10 */

describeQuery
  :
  DESCRIBE
  (
    varOrIriRef+
    | ASTERISK
  )
  datasetClause* whereClause? solutionModifier
  ;

/* sparql 1.1 r11 */

askQuery
  :
  ASK datasetClause* whereClause
  ;

/* sparql 1.1 r12 */

datasetClause
  :
  FROM
  (
    defaultGraphClause
    | namedGraphClause
  )
  ;

/* sparql 1.1 r13 */

defaultGraphClause
  :
  sourceSelector
  ;

/* sparql 1.1 r14 */

namedGraphClause
  :
  NAMED sourceSelector
  ;

/* sparql 1.1 r15 */

sourceSelector
  :
  iriRef
  ;

/* sparql 1.1 r16 */

whereClause
  :
  WHERE? groupGraphPattern
  ;

/* sparql 1.1 r17 */

solutionModifier
  :
  groupClause? havingClause? orderClause? limitOffsetClauses?
  ;

/* sparql 1.1 r18 */

groupClause
  :
  GROUP BY groupCondition+
  ;

/* sparql 1.1 r19 */

groupCondition
  :
  builtInCall
  | functionCall
  | (OPEN_BRACE expression (AS variable)? CLOSE_BRACE)
  | variable
  ;

/* sparql 1.1 r20 */

havingClause
  :
  HAVING havingCondition+
  ;

/* sparql 1.1 r21 */

havingCondition
  :
  constraint
  ;

/* sparql 1.1 r22 */

orderClause
  :
  ORDER BY orderCondition+
  ;

/* sparql 1.1 r23 */

orderCondition
  :
  (
    (
      ASC
      | DESC
    )
    brackettedExpression
  )
  |
  (
    constraint
    | variable
  )
  ;

/* sparql 1.1 r24 */

limitOffsetClauses
  :
  (limitClause offsetClause?)
  | (offsetClause limitClause?)
  ;

/* sparql 1.1 r25 */

limitClause
  :
  LIMIT INTEGER
  ;

/* sparql 1.1 r26 */

offsetClause
  :
  OFFSET INTEGER
  ;

/* sparql 1.1 r27 */

bindingsClause
  :
  (
    BINDINGS variable* OPEN_CURLY_BRACE
    (
      OPEN_BRACE bindingValue+ CLOSE_BRACE
      | (OPEN_BRACE WS* CLOSE_BRACE)
    )*
    CLOSE_CURLY_BRACE
  )?
  ;

/* sparql 1.1 r28 */

bindingValue
  :
  iriRef
  | rdfLiteral
  | numericLiteral
  | booleanLiteral
  | UNDEF
  ;

/* sparql 1.1 r29 */

updateUnit
  :
  update
  ;

/* sparql 1.1 r30 */

update
  :
  prologue update1 (SEMICOLON update)?
  ;

/* sparql 1.1 r31 */

update1
  :
  (
    | load
    | clear
    | drop
    | create
    | insertData
    | deleteData
    | deleteWhere
    | modify
  )
  ;

/* sparql 1.1 r32 */

load
  :
  LOAD iriRef (INTO graphRef)?
  ;

/* sparql 1.1 r33 */

clear
  :
  CLEAR SILENT? graphRefAll
  ;

/* sparql 1.1 r34 */

drop
  :
  DROP SILENT? graphRefAll
  ;

/* sparql 1.1 r35 */

create
  :
  CREATE SILENT? graphRef
  ;

/* sparql 1.1 r36 */

insertData
  :
  //TODO check out what <WS*> means
  INSERT /* <WS*> */
  COMMA DATA quadData
  ;

/* sparql 1.1 r37 */

deleteData
  :
  //TODO check out what <WS*> means
  DELETE /* <WS*> */
  DATA quadData
  ;

/* sparql 1.1 r38 */

deleteWhere
  :
  //TODO check out what <WS*> means
  DELETE /* <WS*> */
  WHERE quadPattern
  ;

/* sparql 1.1 r39 */

modify
  :
  (WITH iriRef)?
  (
    deleteClause insertClause?
    | insertClause
  )
  usingClause* WHERE groupGraphPattern
  ;

/* sparql 1.1 r40 */

deleteClause
  :
  DELETE quadPattern
  ;

/* sparql 1.1 r41 */

insertClause
  :
  INSERT quadPattern
  ;

/* sparql 1.1 r42 */

usingClause
  :
  USING
  (
    iriRef
    | NAMED iriRef
  )
  ;

/* sparql 1.1 r43 */

graphRef
  :
  GRAPH
  | iriRef
  ;

/* sparql 1.1 r44 */

graphRefAll
  :
  graphRef
  | DEFAULT
  | NAMED
  | ALL
  ;

/* sparql 1.1 r45 */

quadPattern
  :
  OPEN_CURLY_BRACE quads CLOSE_CURLY_BRACE
  ;

/* sparql 1.1 r46 */

quadData
  :
  OPEN_CURLY_BRACE quads CLOSE_CURLY_BRACE
  ;

/* sparql 1.1 r47 */

quads
  :
  triplesTemplate? (quadsNotTriples DOT? triplesTemplate?)*
  ;

/* sparql 1.1 r48 */

quadsNotTriples
  :
  GRAPH varOrIriRef OPEN_CURLY_BRACE triplesTemplate CLOSE_CURLY_BRACE
  ;

/* sparql 1.1 r49 */

triplesTemplate
  :
  triplesSameSubject (DOT triplesTemplate?)?
  ;

/* sparql 1.1 r50 */

groupGraphPattern
  :
  OPEN_CURLY_BRACE
  (
    subSelect
    | groupGraphPatternSub
  )
  CLOSE_CURLY_BRACE
  ;

/* sparql 1.1 r51 */

groupGraphPatternSub
  :
  triplesBlock? (graphPatternNotTriples DOT? triplesBlock?)*
  ;

/* sparql 1.1 r52 */

triplesBlock
  :
  triplesSameSubjectPath (DOT triplesBlock?)?
  ;

/* sparql 1.1 r53 */

graphPatternNotTriples
  :
  groupOrUnionGraphPattern
  | optionalGraphPattern
  | minusGraphPattern
  | graphGraphPattern
  | serviceGraphPattern
  | filter
  ;

/* sparql 1.1 r54 */

optionalGraphPattern
  :
  OPTIONAL groupGraphPattern
  ;

/* sparql 1.1 r55 */

graphGraphPattern
  :
  GRAPH varOrIriRef groupGraphPattern
  ;

/* sparql 1.1 r56 */

serviceGraphPattern
  :
  SERVICE varOrIriRef groupGraphPattern
  ;

/* sparql 1.1 r57 */

minusGraphPattern
  :
  MINUS_P groupGraphPattern
  ;

/* sparql 1.1 r58 */

groupOrUnionGraphPattern
  :
  groupGraphPattern (UNION groupGraphPattern)*
  ;

/* sparql 1.1 r59 */

filter
  :
  FILTER constraint
  ;

/* sparql 1.1 r60 */

constraint
  :
  brackettedExpression
  | builtInCall
  | functionCall
  ;

/* sparql 1.1 r61 */

functionCall
  :
  iriRef argList
  ;

/* sparql 1.1 r62 */

argList
  :
  OPEN_BRACE WS* CLOSE_BRACE
  | OPEN_BRACE DISTINCT? expression (COMMA expression)* CLOSE_BRACE
  ;

/* sparql 1.1 r63 */

expressionList
  :
  OPEN_BRACE WS* CLOSE_BRACE
  | OPEN_BRACE expression (COMMA expression)* CLOSE_BRACE
  ;

/* sparql 1.1 r64 */

constructTemplate
  :
  OPEN_CURLY_BRACE constructTriples? CLOSE_CURLY_BRACE
  ;

/* sparql 1.1 r65 */

constructTriples
  :
  triplesSameSubject (DOT constructTriples?)?
  ;

/* sparql 1.1 r66 */

triplesSameSubject
  :
  varOrTerm propertyListNotEmpty
  | triplesNode propertyList
  ;

/* sparql 1.1 r67 */

propertyListNotEmpty
  :
  verb objectList (SEMICOLON (verb objectList)?)*
  ;

/* sparql 1.1 r68 */

propertyList
  :
  propertyListNotEmpty?
  ;

/* sparql 1.1 r69 */

objectList
  :
  object (COMMA object)*
  ;

/* sparql 1.1 r70 */

object
  :
  graphNode
  ;

/* sparql 1.1 r71 */

verb
  :
  varOrIriRef
  | A
  ;

/* sparql 1.1 r72 */

triplesSameSubjectPath
  :
  varOrTerm propertyListNotEmptyPath
  | triplesNode propertyListPath
  ;

/* sparql 1.1 r73 */

propertyListNotEmptyPath
  :
  (
	verbPathOrSimple
  )
  objectList
  (
    SEMICOLON
    (
      (
        verbPathOrSimple
      )
      objectList
    )?
  )*
  ;

/* Added by Pradeep */
verbPathOrSimple
  :
  path
  |variable
  ;
	
/* sparql 1.1 r74 */

propertyListPath
  :
  propertyListNotEmpty?
  ;

/* sparql 1.1 r75 */
/*
verbPath
  :
  path
  ;
*/
/* sparql 1.1 r76 */
/*
verbSimple
  :
  variable
  ;
*/
/* sparql 1.1 r77 */

path
  :
  pathAlternative
  ;

/* sparql 1.1 r78 */

pathAlternative
  :
  pathSequence (PIPE pathSequence)*
  ;

/* sparql 1.1 r79 */

pathSequence
  :
  pathEltOrInverse (DIVIDE pathEltOrInverse)*
  ;

/* sparql 1.1 r80 */

pathElt
  :
  pathPrimary pathMod?
  ;

/* sparql 1.1 r81 */

pathEltOrInverse
  :
  pathElt
  | HAT_LABEL pathElt
  ;

/* sparql 1.1 r82 */

pathMod
  :
  (
    ASTERISK
    | QUESTION_MARK_LABEL
    | PLUS
    | OPEN_CURLY_BRACE
    (
      integer
      (
        COMMA
        (
          CLOSE_CURLY_BRACE
          | integer CLOSE_CURLY_BRACE
        )
        | CLOSE_CURLY_BRACE
      )
      | COMMA integer CLOSE_CURLY_BRACE
    )
  )
  ;

/* sparql 1.1 r83 */

pathPrimary
  :
  iriRef
  | A
  | NOT_SIGN pathNegatedPropertySet
  | OPEN_BRACE path CLOSE_BRACE
  ;

/* sparql 1.1 r84 */

pathNegatedPropertySet
  :
  pathOneInPropertySet
  | OPEN_BRACE (pathOneInPropertySet (PIPE pathOneInPropertySet)*)? CLOSE_BRACE
  ;

/* sparql 1.1 r85 */

pathOneInPropertySet
  :
  iriRef
  | A
  | HAT_LABEL
  (
    iriRef
    | A
  )
  ;

/* sparql 1.1 r86 */

integer
  :
  INTEGER
  ;

/* sparql 1.1 r87 */

triplesNode
  :
  collection
  | blankNodePropertyList
  ;

/* sparql 1.1 r88 */

blankNodePropertyList
  :
  OPEN_SQUARE_BRACE propertyListNotEmpty CLOSE_SQUARE_BRACE
  ;

/* sparql 1.1 r89 */

collection
  :
  OPEN_BRACE graphNode+ CLOSE_BRACE
  ;

/* sparql 1.1 r90 */

graphNode
  :
  varOrTerm
  | triplesNode
  ;

/* sparql 1.1 r91 */

varOrTerm
  :
  variable
  | graphTerm
  ;

/* sparql 1.1 r92 */

varOrIriRef
  :
  variable
  | iriRef
  ;

/* sparql 1.1 r93 */

variable
  :
  VAR1
  | VAR2
  ;

/* sparql 1.1 r94 */

graphTerm
  :
  iriRef
  | rdfLiteral
  | numericLiteral
  | booleanLiteral
  | blankNode
  | OPEN_BRACE WS* CLOSE_BRACE
  ;

/* sparql 1.1 r95 */

expression
  :
  conditionalOrExpression
  ;

/* sparql 1.1 r96 */

conditionalOrExpression
  :
  conditionalAndExpression (OR conditionalAndExpression)*
  ;

/* sparql 1.1 r97 */

conditionalAndExpression
  :
  valueLogical (AND valueLogical)*
  ;

/* sparql 1.1 r98 */

valueLogical
  :
  relationalExpression
  ;

/* sparql 1.1 r99 */

relationalExpression
  :
  numericExpression
  (
    EQUAL numericExpression
    | NOT_EQUAL numericExpression
    | LESS numericExpression
    | GREATER numericExpression
    | LESS_EQUAL numericExpression
    | GREATER_EQUAL numericExpression
    | IN expressionList
    | NOT IN expressionList
  )?
  ;

/* sparql 1.1 r100 */

numericExpression
  :
  additiveExpression
  ;

/* sparql 1.1 r101 */

additiveExpression
  :
  multiplicativeExpression
  (
    PLUS multiplicativeExpression
    | MINUS multiplicativeExpression
    |
    (
      numericLiteralPositive
      | numericLiteralNegative
    )
    (
      (ASTERISK unaryExpression)
      | (DIVIDE unaryExpression)
    )?
  )*
  ;

/* sparql 1.1 r102 */

multiplicativeExpression
  :
  unaryExpression
  (
    ASTERISK unaryExpression
    | DIVIDE unaryExpression
  )*
  ;

/* sparql 1.1 r103 */

unaryExpression
  :
  NOT_SIGN primaryExpression
  | PLUS primaryExpression
  | MINUS primaryExpression
  | primaryExpression
  ;

/* sparql 1.1 r104 */

primaryExpression
  :
  brackettedExpression
  | builtInCall
  | iriRefOrFunction
  | rdfLiteral
  | numericLiteral
  | booleanLiteral
  | variable
  | aggregate
  ;

/* sparql 1.1 r105 */

brackettedExpression
  :
  OPEN_BRACE expression CLOSE_BRACE
  ;

/* sparql 1.1 r106 */

builtInCall
  :
  STR OPEN_BRACE expression CLOSE_BRACE
  | LANG OPEN_BRACE expression CLOSE_BRACE
  | LANGMATCHES OPEN_BRACE expression COMMA expression CLOSE_BRACE
  | DATATYPE OPEN_BRACE expression CLOSE_BRACE
  | BOUND OPEN_BRACE variable CLOSE_BRACE
  | IRI OPEN_BRACE expression CLOSE_BRACE
  | URI OPEN_BRACE expression CLOSE_BRACE
  | BNODE
  (
    (OPEN_BRACE variable CLOSE_BRACE)
    | OPEN_BRACE WS* CLOSE_BRACE
  )
  | COALESCE expressionList
  | IF OPEN_BRACE expression COMMA expression COMMA expression CLOSE_BRACE
  | STRLANG OPEN_BRACE expression COMMA expression CLOSE_BRACE
  | STRDT OPEN_BRACE expression COMMA expression CLOSE_BRACE
  | SAMETERM OPEN_BRACE expression COMMA expression CLOSE_BRACE
  | ISIRI OPEN_BRACE expression CLOSE_BRACE
  | ISURI OPEN_BRACE expression CLOSE_BRACE
  | ISBLANK OPEN_BRACE expression CLOSE_BRACE
  | ISLITERAL OPEN_BRACE expression CLOSE_BRACE
  | ISNUMERIC OPEN_BRACE expression CLOSE_BRACE
  | regexExpression
  | existsFunc
  | notExistsFunc
  ;

/* sparql 1.1 r107 */

regexExpression
  :
  REGEX OPEN_BRACE expression COMMA expression (COMMA expression)? CLOSE_BRACE
  ;

/* sparql 1.1 r108 */

existsFunc
  :
  EXISTS groupGraphPattern
  ;

/* sparql 1.1 r109 */

notExistsFunc
  :
  NOT EXISTS groupGraphPattern
  ;

/* sparql 1.1 r110 */

aggregate
  :
  (
    COUNT OPEN_BRACE DISTINCT?
    (
      ASTERISK
      | expression
    )
    CLOSE_BRACE
    | SUM OPEN_BRACE DISTINCT? expression CLOSE_BRACE
    | MIN OPEN_BRACE DISTINCT? expression CLOSE_BRACE
    | MAX OPEN_BRACE DISTINCT? expression CLOSE_BRACE
    | AVG OPEN_BRACE DISTINCT? expression CLOSE_BRACE
    | SAMPLE OPEN_BRACE DISTINCT? expression CLOSE_BRACE
    | GROUP_CONCAT OPEN_BRACE DISTINCT? expression (SEMICOLON SEPARATOR EQUAL string)? CLOSE_BRACE
  )
  ;

/* sparql 1.1 r111 */

iriRefOrFunction
  :
  iriRef argList?
  ;

/* sparql 1.1 r112 */

rdfLiteral
  :
  string
  (
    LANGTAG
    | (REFERENCE iriRef)
  )?
  ;

/* sparql 1.1 r113 */

numericLiteral
  :
  numericLiteralUnsigned
  | numericLiteralPositive
  | numericLiteralNegative
  ;

/* sparql 1.1 r114 */

numericLiteralUnsigned
  :
  INTEGER
  | DECIMAL
  | DOUBLE
  ;

/* sparql 1.1 r115 */

numericLiteralPositive
  :
  INTEGER_POSITIVE
  | DECIMAL_POSITIVE
  | DOUBLE_POSITIVE
  ;

/* sparql 1.1 r116 */

numericLiteralNegative
  :
  INTEGER_NEGATIVE
  | DECIMAL_NEGATIVE
  | DOUBLE_NEGATIVE
  ;

/* sparql 1.1 r117 */

booleanLiteral
  :
  TRUE
  | FALSE
  ;

/* sparql 1.1 r118 */

string
  :
  STRING_LITERAL1
  | STRING_LITERAL2
  | STRING_LITERAL_LONG1
  | STRING_LITERAL_LONG2
  ;

/* sparql 1.1 r119 */

iriRef
  :
  IRI_REF
  | prefixedName
  ;

/* sparql 1.1 r120 */

prefixedName
  :
  PNAME_LN
  | PNAME_NS
  ;

/* sparql 1.1 r121 */

blankNode
  :
  BLANK_NODE_LABEL
  | OPEN_SQUARE_BRACE WS* CLOSE_SQUARE_BRACE
  ;

// $>

// $<Lexer

DATA
  :
  'data'
  ;

MODIFY
  :
  'modify'
  ;

DELETE
  :
  'delete'
  ;

INSERT
  :
  'insert'
  ;

INTO
  :
  'into'
  ;

LOAD
  :
  'load'
  ;

CLEAR
  :
  'clear'
  ;

CREATE
  :
  'create'
  ;

SILENT
  :
  'silent'
  ;

DROP
  :
  'drop'
  ;

DEFAULT
  :
  'default'
  ;

ALL
  :
  'all'
  ;

SERVICE
  :
  'service'
  ;

MINUS_P
  :
  'minus'
  ;

EXISTS
  :
  'exists'
  ;

UNSAID
  :
  'unsaid'
  ;

HAVING
  :
  'having'
  ;

COUNT
  :
  'count'
  ;

SUM
  :
  'sum'
  ;

MIN
  :
  'min'
  ;

MAX
  :
  'max'
  ;

AVG
  :
  'avg'
  ;

SAMPLE
  :
  'sample'
  ;

GROUP_CONCAT
  :
  'group_concat'
  ;

SEPARATOR
  :
  'separator'
  ;

USING
  :
  'using'
  ;

COALESCE
  :
  'coalesce'
  ;

DEFINE
  :
  'define'
  ;

IF
  :
  'if'
  ;

BASE
  :
  'base'
  ;

PREFIX
  :
  'PREFIX'
  ;

IN
  :
  'in'
  ;

NOT
  :
  'not'
  ;

SELECT
  :
  'SELECT'
  ;

DISTINCT
  :
  'DISTINCT'
  ;

REDUCED
  :
  'REDUCED'
  ;

CONSTRUCT
  :
  'CONSTRUCT'
  ;

DESCRIBE
  :
  'DESCRIBE'
  ;

ASK
  :
  'ASK'
  ;

FROM
  :
  'FROM'
  ;

NAMED
  :
  'named'
  ;

WHERE
  :
  'WHERE'
  ;

ORDER
  :
  'order'
  ;

GROUP
  :
  'group'
  ;

BY
  :
  'by'
  ;

ASC
  :
  'asc'
  ;

DESC
  :
  'desc'
  ;

LIMIT
  :
  'LIMIT'
  ;

OFFSET
  :
  'offset'
  ;

BINDINGS
  :
  'bindings'
  ;

WITH
  :
  'with'
  ;

OPTIONAL
  :
  'OPTIONAL'
  ;

GRAPH
  :
  'graph'
  ;

UNION
  :
  'UNION'
  ;

FILTER
  :
  'FILTER'
  ;

A
  :
  ('a')
  ;

AS
  :
  'as'
  ;

STR
  :
  'str'
  ;

LANG
  :
  'lang'
  ;

LANGMATCHES
  :
  'langmatches'
  ;

DATATYPE
  :
  'datatype'
  ;

BOUND
  :
  'bound'
  ;

SAMETERM
  :
  'sameterm'
  ;

IRI
  :
  'iri'
  ;

URI
  :
  'uri'
  ;

BNODE
  :
  'bnode'
  ;

STRLANG
  :
  'strlang'
  ;

STRDT
  :
  'strdt'
  ;

ISIRI
  :
  'isiri'
  ;

ISURI
  :
  'isuri'
  ;

ISBLANK
  :
  'isblank'
  ;

ISLITERAL
  :
  'isliteral'
  ;

ISNUMERIC
  :
  'isnumeric'
  ;

REGEX
  :
  'regex'
  ;

TRUE
  :
  'true'
  ;

FALSE
  :
  'false'
  ;

IRI_REF
  :
  LESS
  ( options {greedy=false;}:
    ~(
       '<'
      |'>' 
      | '"'
      | '{' 
      | '}'
      | '|'
      | '^'
      | '\\'
      | '`'
      | '\u0000'..'\u0020'
     )
  )* 
  GREATER
  ;

PNAME_NS
  :
  p=PN_PREFIX? ':'
  ;

PNAME_LN
  :
  PNAME_NS PN_LOCAL
  ;

VAR1
  :
  '?' v=VARNAME
  ;

VAR2
  :
  '$' v=VARNAME
  ;

LANGTAG
  :
  '@' ( ('a'..'z'))+
  (
    MINUS
    (
      ('a'..'z') ('0'..'9')
    )+
  )*
  ;

INTEGER
  :
  ('0'..'9')+
  ;

DECIMAL
  :
  ('0'..'9')+ DOT ('0'..'9')*
  | DOT ('0'..'9')+
  ;

DOUBLE
  :
  DIGIT+ DOT DIGIT* EXPONENT
  | DOT DIGIT+ EXPONENT
  | DIGIT+ EXPONENT
  ;

fragment
DIGIT
  :
  '0'..'9'
  ;

INTEGER_POSITIVE
  :
  PLUS n=INTEGER
  ;

DECIMAL_POSITIVE
  :
  PLUS n=DECIMAL
  ;

DOUBLE_POSITIVE
  :
  PLUS n=DOUBLE
  ;

INTEGER_NEGATIVE
  :
  MINUS n=INTEGER
  ;

DECIMAL_NEGATIVE
  :
  MINUS n=DECIMAL
  ;

DOUBLE_NEGATIVE
  :
  MINUS n=DOUBLE
  ;

fragment
EXPONENT
  :
  'e'
  (
    PLUS
    | MINUS
  )?
  ('0'..'9')+
  ;

STRING_LITERAL1
  :
  '\''
  ( options {greedy=false;}:
    ~(
      '\''
      | '\\'
      | '\n'
      | '\r'
     )
    | ECHAR
    | UNICODE_CHAR
  )*
  '\''
  ;

STRING_LITERAL2
  :
  '"'
  ( options {greedy=false;}:
    ~(
      '\"'
      | '\\'
      | '\n'
      | '\r'
     )
    | ECHAR
    | UNICODE_CHAR
  )*
  '"'
  ;

STRING_LITERAL_LONG1
  :
  '\'\'\''
  ( options {greedy=false;}:
    (
      '\''
      | '\'\''
    )?
    (
      ~(
        '\''
        | '\\'
       )
      | ECHAR
      | UNICODE_CHAR
    )
  )*
  '\'\'\''
  ;

STRING_LITERAL_LONG2
  :
  '"""'
  ( options {greedy=false;}:
    (
      '"'
      | '""'
    )?
    (
      ~(
        '"'
        | '\\'
       )
      | ECHAR
      | UNICODE_CHAR
    )
  )*
  '"""'
  ;

fragment
ECHAR
  :
  '\\'
  (
    't'
    | 'b'
    | 'n'
    | 'r'
    | 'f'
    | '\\'
    | '"'
    | '\''
  )
  ;

WS
  :
  ((
    ' '
    | '\t'
    | EOL
  )+) -> skip
  ;

fragment
PN_CHARS_BASE
  :
  'a'..'z'
  | 'A'..'Z'
  //  | '\u00C0'..'\u00D6'
  //  | '\u00D8'..'\u00F6'
  //  | '\u00F8'..'\u02FF'
  //  | '\u0370'..'\u037D'
  //  | '\u037F'..'\u1FFF'
  //  | '\u200C'..'\u200D'
  //  | '\u2070'..'\u218F'
  //  | '\u2C00'..'\u2FEF'
  //  | '\u3001'..'\uD7FF'
  //  | '\uF900'..'\uFDCF'
  //  | '\uFDF0'..'\uFFFD'
  ;

fragment
PN_CHARS_U
  :
  PN_CHARS_BASE
  | '_'
  ;

fragment
VARNAME
  :
  (
    PN_CHARS_U
    | ('0'..'9')
  )
  (
    PN_CHARS_U
    | ('0'..'9')
  //    | '\u00B7'
  //    | '\u0300'..'\u036F'
  //    | '\u203F'..'\u2040'
  )*
  ;

fragment
PN_CHARS
  :
  PN_CHARS_U
  | MINUS
  | ('0'..'9')
  //  | '\u00B7'
  //  | '\u0300'..'\u036F'
  //  | '\u203F'..'\u2040'
  ;

fragment
PN_PREFIX
  :
  PN_CHARS_BASE
  (
    (
      PN_CHARS
      | DOT
    )*
    PN_CHARS
  )?
  ;

fragment
PN_LOCAL
  :
  (
    PN_CHARS_U
    | ('0'..'9')
  )
  (
    (
      PN_CHARS
      | DOT
    )*
    PN_CHARS
  )?
  ;

BLANK_NODE_LABEL
  :
  '_:' t=PN_LOCAL
  ;

REFERENCE
  :
  '^^'
  ;

AND
  :
  '&&'
  ;

PIPE
  :
  '|'
  ;

OR
  :
  '||'
  ;

COMMENT
  :
  ('#' .* EOL) -> skip
  ;

fragment
EOL
  :
  '\n'
  | '\r'
  ;

OPEN_CURLY_BRACE
  :
  '{'
  ;

CLOSE_CURLY_BRACE
  :
  '}'
  ;

SEMICOLON
  :
  ';'
  ;

DOT
  :
  '.'
  ;

PLUS
  :
  '+'
  ;

MINUS
  :
  '-'
  ;

ASTERISK
  :
  '*'
  ;

COMMA
  :
  ','
  ;

NOT_SIGN
  :
  '!'
  ;

DIVIDE
  :
  '/'
  ;

EQUAL
  :
  '='
  ;

LESS
  :
  '<'
  ;

GREATER
  :
  '>'
  ;

OPEN_BRACE
  :
  '('
  ;

CLOSE_BRACE
  :
  ')'
  ;

LESS_EQUAL
  :
  '<='
  ;

GREATER_EQUAL
  :
  '>='
  ;

NOT_EQUAL
  :
  '!='
  ;

OPEN_SQUARE_BRACE
  :
  '['
  ;

CLOSE_SQUARE_BRACE
  :
  ']'
  ;

HAT_LABEL
  :
  '^'
  ;

QUESTION_MARK_LABEL
  :
  '?'
  ;

fragment
UNICODE_CHAR
  :
  '\\' 'u' HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT
  ;

fragment
HEX_DIGIT
  :
  '0'..'9'
  | 'a'..'f'
  | 'A'..'F'
  ;

UNDEF
  :
  'undef'
  ;

//BACKQUOTE
//  :
//  '`'
//  ;
//
//PLUSGREATER
//  :
//  '+>'
//  ;
//
//ASTERISKGREATER
//  :
//  '*>'
//  ;

// $>
