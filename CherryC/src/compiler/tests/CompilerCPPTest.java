package compiler.tests;

import compiler.LangCompiler;
import compiler.Lexer;
import compiler.Parser;
import compiler.ast.ASTClass;
import compiler.backends.CompilerCPP;
import compiler.lib.IndentPrinter;
import org.junit.jupiter.api.Test;

import java.io.ByteArrayInputStream;
import java.io.InputStream;
import java.io.PushbackInputStream;
import java.nio.charset.StandardCharsets;

import static org.junit.jupiter.api.Assertions.*;

/**
 * @author alex
 * @date 28/04/17.
 */
class CompilerCPPTest
{

	void testCompiler(String testName, String testString)
	{
		System.out.println("=== " + testName + " ===");

		InputStream inputStream = new ByteArrayInputStream(testString.getBytes(StandardCharsets.UTF_8));
		PushbackInputStream i = new PushbackInputStream(inputStream);

		LangCompiler c = new CompilerCPP(new IndentPrinter(System.out));


		Lexer l = new Lexer(i, testName);
		Parser p = new Parser(l);

		ASTClass cl = new ASTClass(testName, null);

		p.parseFile(cl);

		c.compileClass(cl);

		System.out.println('\n');
	}

	@Test
	void testAll()
	{
		testCompiler("Assignment", "helloWorld := 42");
		testCompiler("Expressions", "B:=2\nA:= B + 2");
		testCompiler("IfAndElse", "B:=2\nif B == 1\n\tB = 42\nelse\n\tB=32");
		testCompiler("Loops", "B := 0\nloop A:=1, A < 10, A = A + 1\n\tB = B + 1");
	}
}