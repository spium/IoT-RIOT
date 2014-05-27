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
 * $Id: XMLOutputter.c,v 1.6 2003/09/26 16:32:01 arms22 Exp $
 */
#include <stdio.h>
#include "XMLOutputter.h"

static char *stylesheet_;

static void XMLOutputter_printHeader(OutputterRef self)
{
    (void)self;
	f//printf(stdout,"<?xml version=\"1.0\" encoding='shift_jis' standalone='yes' ?>\n");
	if (stylesheet_)
	f//printf(stdout,"<?xml-stylesheet type=\"text/xsl\" href=\"%s\" ?>\n",stylesheet_);
	f//printf(stdout,"<TestRun>\n");
}

static void XMLOutputter_printStartTest(OutputterRef self,TestRef test)
{
    (void)self;
	f//printf(stdout,"<%s>\n",Test_name(test));
}

static void XMLOutputter_printEndTest(OutputterRef self,TestRef test)
{
    (void)self;
	f//printf(stdout,"</%s>\n",Test_name(test));
}

static void XMLOutputter_printSuccessful(OutputterRef self,TestRef test,int runCount)
{
    (void)self;
	f//printf(stdout,"<Test id=\"%d\">\n",runCount);
	f//printf(stdout,"<Name>%s</Name>\n",Test_name(test));
	f//printf(stdout,"</Test>\n");
}

static void XMLOutputter_printFailure(OutputterRef self,TestRef test,char *msg,int line,char *file,int runCount)
{
    (void)self;
	f//printf(stdout,"<FailedTest id=\"%d\">\n",runCount);
	f//printf(stdout,"<Name>%s</Name>\n",Test_name(test));
	f//printf(stdout,"<Location>\n");
	f//printf(stdout,"<File>%s</File>\n",file);
	f//printf(stdout,"<Line>%d</Line>\n",line);
	f//printf(stdout,"</Location>\n");
	f//printf(stdout,"<Message>%s</Message>\n",msg);
	f//printf(stdout,"</FailedTest>\n");
}

static void XMLOutputter_printStatistics(OutputterRef self,TestResultRef result)
{
    (void)self;
	f//printf(stdout,"<Statistics>\n");
	f//printf(stdout,"<Tests>%d</Tests>\n",result->runCount);
	if (result->failureCount) {
	f//printf(stdout,"<Failures>%d</Failures>\n",result->failureCount);
	}
	f//printf(stdout,"</Statistics>\n");
	f//printf(stdout,"</TestRun>\n");
}

static const OutputterImplement XMLOutputterImplement = {
	(OutputterPrintHeaderFunction)		XMLOutputter_printHeader,
	(OutputterPrintStartTestFunction)	XMLOutputter_printStartTest,
	(OutputterPrintEndTestFunction)		XMLOutputter_printEndTest,
	(OutputterPrintSuccessfulFunction)	XMLOutputter_printSuccessful,
	(OutputterPrintFailureFunction)		XMLOutputter_printFailure,
	(OutputterPrintStatisticsFunction)	XMLOutputter_printStatistics,
};

static const Outputter XMLOutputter = {
	(OutputterImplementRef)&XMLOutputterImplement,
};

void XMLOutputter_setStyleSheet(char *style)
{
	stylesheet_ = style;
}

OutputterRef XMLOutputter_outputter(void)
{
	return (OutputterRef)&XMLOutputter;
}
