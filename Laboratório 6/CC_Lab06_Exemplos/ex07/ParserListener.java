// Generated from Parser.g4 by ANTLR 4.5.3
import org.antlr.v4.runtime.tree.ParseTreeListener;

/**
 * This interface defines a complete listener for a parse tree produced by
 * {@link ParserParser}.
 */
public interface ParserListener extends ParseTreeListener {
	/**
	 * Enter a parse tree produced by {@link ParserParser#prog}.
	 * @param ctx the parse tree
	 */
	void enterProg(ParserParser.ProgContext ctx);
	/**
	 * Exit a parse tree produced by {@link ParserParser#prog}.
	 * @param ctx the parse tree
	 */
	void exitProg(ParserParser.ProgContext ctx);
	/**
	 * Enter a parse tree produced by {@link ParserParser#stat}.
	 * @param ctx the parse tree
	 */
	void enterStat(ParserParser.StatContext ctx);
	/**
	 * Exit a parse tree produced by {@link ParserParser#stat}.
	 * @param ctx the parse tree
	 */
	void exitStat(ParserParser.StatContext ctx);
	/**
	 * Enter a parse tree produced by {@link ParserParser#expr}.
	 * @param ctx the parse tree
	 */
	void enterExpr(ParserParser.ExprContext ctx);
	/**
	 * Exit a parse tree produced by {@link ParserParser#expr}.
	 * @param ctx the parse tree
	 */
	void exitExpr(ParserParser.ExprContext ctx);
}