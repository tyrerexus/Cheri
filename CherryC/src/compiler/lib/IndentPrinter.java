package compiler.lib;

import java.io.PrintStream;

/**
 * This class can print strings and objects while indenting lines by a counter.
 *
 * @author Tyrerexus
 * @date 4/12/17.
 */
public class IndentPrinter
{
	private PrintStream destination;
	public int indentation;
	private boolean new_line_clean = true;

	public IndentPrinter(PrintStream destination)
	{
		this.destination = destination;
	}

	public void println(Object what)
	{
		if (new_line_clean)
		{
			for (int i = 0; i < indentation; i++)
			{
				destination.print("  ");
			}
		}
		destination.println(what);
		new_line_clean = true;
	}

	public void println()
	{
		println("");
	}

	public void print(Object what)
	{
		if (new_line_clean)
		{
			for (int i = 0; i < indentation; i++)
			{
				destination.print("  ");
			}
		}
		destination.print(what);
		new_line_clean = false;
	}
}