#include <cppunit/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/XmlOutputter.h>
#include "InputPacketStreamFileTest.h"

using namespace CppUnit;

CPPUNIT_TEST_SUITE_REGISTRATION(InputPacketStreamFileTest);

int main(int argc, char* argv[])
{
	TestResult testresult;

	// register listener for collecting the test-results
	TestResultCollector collectedresults;
	testresult.addListener(&collectedresults);

	// register listener for per-test progress output
	BriefTestProgressListener progress;
	testresult.addListener(&progress);

	// insert test-suite at test-runner by registry
	TestRunner testrunner;
	testrunner.addTest(TestFactoryRegistry::getRegistry().makeTest());
	testrunner.run(testresult);

	// output results in compiler-format
	CompilerOutputter compileroutputter(&collectedresults, std::cerr);
	compileroutputter.write();

	// Output XML for Jenkins CPPunit plugin
	ofstream xmlFileOut("cppTestBasicMathResults.xml");
	XmlOutputter xmlOut(&collectedresults, xmlFileOut);
	xmlOut.write();
	
	// return 0 if tests were successful
	return collectedresults.wasSuccessful() ? 0 : 1;
}
