/**
 *  @file   TestPandora/include/TestMiscellaneous.h
 * 
 *  @brief  Header file for the Miscellaneous test-class.
 * 
 *  $Log: $
 */
#ifndef TEST_MISCELLANEOUS_H
#define TEST_MISCELLANEOUS_H 1

#include "Pandora/PandoraInternal.h"
#include "Pandora/Pandora.h"

#include "StatusCodes.h"

#include <assert.h>
#include <iostream>
#include <iomanip>

namespace pandora
{

/**
 *  @brief TestMiscellaneous class
 */
class TestMiscellaneous 
{
public:
    /**
     *  @brief  test the creation of a histogram and producing the xml description
     */
    StatusCode Test_Histogram1DToXml();

    /**
     *  @brief  test the creation of a histogram, the xml production and the reading in of xml
     */
    StatusCode Test_Histogram1DToAndFromXml();

    /**
     *  @brief  test the creation of a histogram, the xml production and the reading in of xml
     */
    StatusCode Test_Histogram2DToAndFromXml();

    /**
     *  @brief  test the creation of a histogram, the xml production and the reading in of xml
     */
    StatusCode Test_MultipleHistogram2DToAndFromXml();

    /**
     *  @brief  test the creation of a histogram, the xml production and the reading in of xml
     */
    StatusCode Test_Histogram2DToAndFromXmlIrreglularBins();

    /**
     *  @brief  test all the available methods
     */
    StatusCode Test_All();
	
};

} // namespace pandora

#endif
