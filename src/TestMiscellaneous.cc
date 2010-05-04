/**
 *  @file   TestPandora/src/TestMiscellaneous.cc
 * 
 *  @brief  Implementation of the tester for the mc manager class.
 * 
 *  $Log: $
 */

#include "Objects/MCParticle.h"
#include "Pandora/Pandora.h"
#include "Xml/tinyxml.h"

#include "TestMiscellaneous.h"

#include "Algorithms/Clustering/ECalPhotonClusteringAlgorithm.h"

#include <assert.h>
#include <iostream>

namespace pandora
{

StatusCode TestMiscellaneous::Test_Histogram1DToXml()
{
    std::cout << "--- --- Histogram1DToXml | START ------------------------------" << std::endl;

    Histogram1D h( "try", 10,3.0, 13.0 );
    for( double x = 2.0; x < 15.0; x += 0.1 )
    {
        h.Fill( x );
    }

    TiXmlDocument doc("Histo");

    TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
    TiXmlElement * element = NULL;
    h.WriteToXml( element );
    doc.LinkEndChild( decl );
    doc.LinkEndChild( element );
    
    doc.Print();
    
    std::cout << "--- --- Histogram1DToXml | STOP ------------------------------" << std::endl;
    return STATUS_CODE_SUCCESS;
}

StatusCode TestMiscellaneous::Test_Histogram1DToAndFromXml()
{
    std::cout << "--- --- Histogram1DToAndFromXml | START ------------------------------" << std::endl;

    Histogram1D h( "writeAndRead", 10,3.0, 13.0 );
    for( double x = 5.0; x < 15.0; x += 0.1 )
    {
        h.Fill( x, x*x );
    }

    TiXmlDocument doc("Histo");

    TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
    TiXmlElement * element = NULL;
    h.WriteToXml( element );
    doc.LinkEndChild( decl );
    doc.LinkEndChild( element );

    
    doc.Print();
    doc.SaveFile( "writeAndRead.xml" );

    std::cout << "------------- written" << std::endl;

    TiXmlDocument docRead("writeAndRead.xml");

    docRead.LoadFile();
    TiXmlElement * loadElement = doc.FirstChildElement();
    Histogram1D h2( *loadElement );

    h2.Print( std::cout );

    
    std::cout << "--- --- Histogram1DToAndFromXml | STOP ------------------------------" << std::endl;
    return STATUS_CODE_SUCCESS;
}


StatusCode TestMiscellaneous::Test_Histogram2DToAndFromXml()
{
    std::cout << "--- --- Histogram1DToAndFromXml | START ------------------------------" << std::endl;

    Histogram2D h( "histoWriteAndRead2D", 10,3.0, 13.0, 5, -35., -15. );
    for( float x = 2.0; x < 15.0; x += 0.1 )
    {
        for( float y = -40.0; y < 2.0; y += 0.3 )
        {
            h.Fill( x, y, x*x+y );
        }
    }

    TiXmlDocument doc("Histo2D");

    TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
    TiXmlElement * element = NULL;
    h.WriteToXml( element );
    doc.LinkEndChild( decl );
    doc.LinkEndChild( element );

    
    doc.Print();
    doc.SaveFile( "writeAndRead2D.xml" );

    std::cout << "------------- written" << std::endl;

    TiXmlDocument docRead("writeAndRead2D.xml");

    docRead.LoadFile();
    TiXmlElement * loadElement = doc.FirstChildElement();
    Histogram2D h2( *loadElement );

    h2.Print( std::cout );

    
    std::cout << "--- --- Histogram2DToAndFromXml | STOP ------------------------------" << std::endl;
    return STATUS_CODE_SUCCESS;
}

StatusCode TestMiscellaneous::Test_Histogram2DToAndFromXmlIrreglularBins()
{
    std::cout << "--- --- Histogram1DToAndFromXmlIrregularBins | START ------------------------------" << std::endl;

    std::vector<float> binBordersX;
    binBordersX.push_back( 3.3 );
    binBordersX.push_back( 5.5 );
    binBordersX.push_back( 6.6 );
    binBordersX.push_back( 18.19 );

    std::vector<float> binBordersY;
    binBordersY.push_back( -2.0 );
    binBordersY.push_back( 20.0 );
    binBordersY.push_back( 18.0 );
    binBordersY.push_back( 4.0 );

    Histogram2D h( "histoWriteAndRead2D", binBordersX, 5, -35., -15. );
    for( float x = 2.0; x < 15.0; x += 0.1 )
    {
        for( float y = -40.0; y < 2.0; y += 0.3 )
        {
            h.Fill( x, y, x*x+y );
        }
    }

    TiXmlDocument doc("Histo2D");

    TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
    TiXmlElement * element = NULL;
    h.WriteToXml( element );
    doc.LinkEndChild( decl );
    doc.LinkEndChild( element );

    
    doc.Print();
    doc.SaveFile( "writeAndRead2DIrregularBins.xml" );

    std::cout << "------------- written" << std::endl;

    TiXmlDocument docRead("writeAndRead2DIrregularBins.xml");

    docRead.LoadFile();
    TiXmlElement * loadElement = docRead.FirstChildElement();
    Histogram2D h2( *loadElement );

    h2.Print( std::cout );

    
    std::cout << "--- --- Histogram2DToAndFromXmlIrregularBins | STOP ------------------------------" << std::endl;
    return STATUS_CODE_SUCCESS;
}

StatusCode TestMiscellaneous::Test_MultipleHistogram2DToAndFromXml()
{
    std::cout << "--- --- MultipleHistogram1DToAndFromXml | START ------------------------------" << std::endl;

    Histogram2D h( "histoWriteAndRead2D", 10,3.0, 13.0, 5, -35., -15. );
    for( float x = 2.0; x < 15.0; x += 0.1 )
    {
        for( float y = -40.0; y < 2.0; y += 0.3 )
        {
            h.Fill( x, y, x*x+y );
        }
    }

    Histogram2D hx( "histoWriteAndRead2D_alternative", 10,3.0, 13.0, 5, -35., -15. );
    for( float x = 2.0; x < 15.0; x += 0.5 )
    {
        for( float y = -40.0; y < 2.0; y += 0.9 )
        {
            hx.Fill( x, y, x*x+y );
        }
    }

    TiXmlDocument doc("multipleHistos2D");

    TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
    doc.LinkEndChild( decl );

    TiXmlElement * element = NULL;
    h.WriteToXml( element );
    doc.LinkEndChild( element );
    hx.WriteToXml( element );
    doc.LinkEndChild( element );

    
    doc.Print();
    doc.SaveFile( "multipleWriteAndRead2D.xml" );

    std::cout << "------------- written" << std::endl;

    TiXmlDocument docRead("multipleWriteAndRead2D.xml");

    docRead.LoadFile();
    TiXmlElement * loadElement = doc.FirstChildElement();
    Histogram2D h2( *loadElement );
    Histogram2D hx2( *loadElement );

    h2.Print( std::cout );
    hx2.Print( std::cout );

    
    std::cout << "--- --- MultipleHistogram2DToAndFromXml | STOP ------------------------------" << std::endl;
    return STATUS_CODE_SUCCESS;
}


StatusCode TestMiscellaneous::Test_All()
{
    std::cout << "--- --- ALL | START ------------------------------" << std::endl;
    assert( Test_Histogram1DToXml() == STATUS_CODE_SUCCESS );
    assert( Test_Histogram1DToAndFromXml() == STATUS_CODE_SUCCESS );
    assert( Test_Histogram2DToAndFromXml() == STATUS_CODE_SUCCESS );
    assert( Test_MultipleHistogram2DToAndFromXml() == STATUS_CODE_SUCCESS );
    assert( Test_Histogram2DToAndFromXmlIrreglularBins() == STATUS_CODE_SUCCESS );

    std::cout << "--- --- ALL | END ------------------------------" << std::endl;
    return STATUS_CODE_SUCCESS;
}

} // namespace pandora
