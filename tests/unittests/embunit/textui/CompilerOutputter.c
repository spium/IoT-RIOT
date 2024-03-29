/*
 * COPYRIGHT AND PERMISSION NOTICE
 *
 * Copyright (c) 2003 Embedded Unit Project
 *
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, and/or sell copies of the Software, and to permit persons
 * to whom the Software is furnished to do so, provided that the above
 * copyright notice(s) and this permission notice appear in all copies
 * of the Software and that both the above copyright notice(s) and this
 * permission notice appear in supporting documentation.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT
 * OF THIRD PARTY RIGHTS. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * HOLDERS INCLUDED IN THIS NOTICE BE LIABLE FOR ANY CLAIM, OR ANY
 * SPECIAL INDIRECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES WHATSOEVER
 * RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF
 * CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Except as contained in this notice, the name of a copyright holder
 * shall not be used in advertising or otherwise to promote the sale,
 * use or other dealings in this Software without prior written
 * authorization of the copyright holder.
 *
 * $Id: CompilerOutputter.c,v 1.2 2003/09/06 13:28:27 arms22 Exp $
 */
#include <stdio.h>
#include "CompilerOutputter.h"

static void CompilerOutputter_printHeader(OutputterRef self,TestRef test)
{
    (void)self;
    (void)test;
}

static void CompilerOutputter_printStartTest(OutputterRef self,TestRef test)
{
    (void)self;
    (void)test;
}

static void CompilerOutputter_printEndTest(OutputterRef self,TestRef test)
{
    (void)self;
    (void)test;
}

static void CompilerOutputter_printSuccessful(OutputterRef self,TestRef test,int runCount)
{
    (void)self;
    (void)test;
    (void)runCount;
}

static void CompilerOutputter_printFailure(OutputterRef self,TestRef test,char *msg,int line,char *file,int runCount)
{
    (void)self;
    (void)runCount;
	fprintf(stdout,"%s %d: %s: %s\n", file, line, Test_name(test), msg);
}

static void CompilerOutputter_printStatistics(OutputterRef self,TestResultRef result)
{
    (void)self;
    (void)result;
}

static const OutputterImplement CompilerOutputterImplement = {
	(OutputterPrintHeaderFunction)		CompilerOutputter_printHeader,
	(OutputterPrintStartTestFunction)	CompilerOutputter_printStartTest,
	(OutputterPrintEndTestFunction)		CompilerOutputter_printEndTest,
	(OutputterPrintSuccessfulFunction)	CompilerOutputter_printSuccessful,
	(OutputterPrintFailureFunction)		CompilerOutputter_printFailure,
	(OutputterPrintStatisticsFunction)	CompilerOutputter_printStatistics,
};

static const Outputter CompilerOutputter = {
	(OutputterImplementRef)&CompilerOutputterImplement,
};

OutputterRef CompilerOutputter_outputter(void)
{
	return (OutputterRef)&CompilerOutputter;
}
