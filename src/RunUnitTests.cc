/**
 *  @file   TestPandora/src/TestPandora.cc
 * 
 *  @brief  The test pandora application entry point.
 * 
 *  $Log: $
 */

#include "TestMCManager.h"
#include "TestCaloHitManager.h"
#include "TestMiscellaneous.h"

#include "Algorithms/Clustering/ECalPhotonClusteringAlgorithm.h"

#include <iostream>

//#include "PandoraMonitoringApi.h"

#include "TTreeWrapper.h"
#include <vector>

#define TEST_VECTORS 1

int main()
{
    std::cout << "--- TEST : Monitoring/TTreeWrapper | START ----------------------------------" << std::endl;
    pandora_monitoring::TTreeWrapper m_treeWrapper;
    float  f0 = 1.1;
    int    i0 = 2;
    double d0 = 3.3;

    typedef std::vector<float>  FVEC;
    typedef std::vector<double> DVEC;
    typedef std::vector<int>    IVEC;

    FVEC* vf0 = new FVEC();
    DVEC* vd0 = new DVEC();
    IVEC* vi0 = new IVEC();

    std::cout << "setfloat " << (m_treeWrapper.Set<float> ( "testTree", "f0", f0 )?"successful":"failure") << std::endl;
    m_treeWrapper.Set<int>   ( "testTree", "i0", i0 );
    m_treeWrapper.Set<double>( "testTree", "d0", d0 );

    // fill some arbitrary numbers into the vector
    for( int i = 0; i < 11; ++i )
    {
        vf0->push_back(i*0.53);
        vd0->push_back(i*0.00037);
        vi0->push_back(i*i);
    }
#ifdef TEST_VECTORS
    m_treeWrapper.Set<FVEC*>( "testVectorTree", "vf0", vf0 );
    m_treeWrapper.Set<DVEC*>( "testVectorTree", "vd0", vd0 );
    m_treeWrapper.Set<IVEC*>( "testVectorTree", "vi0", vi0 );
#endif

    m_treeWrapper.Fill( "testTree" );
#ifdef TEST_VECTORS
    m_treeWrapper.Fill( "testVectorTree" );
#endif

    for( int i = 0; i < 20; ++i )
    {
        f0 += 1.1;
        i0 += 2;
        d0 += 3.14;

        m_treeWrapper.Set<float> ( "testTree", "f0", f0 );
        m_treeWrapper.Set<int>   ( "testTree", "i0", i0 );
        m_treeWrapper.Set<double>( "testTree", "d0", d0 );

        
        vf0->clear();
        vd0->clear();
        vi0->clear();
        for( int j = 0; j < 5; ++j )
        {
            vf0->push_back(i*j*0.53);
            vd0->push_back(i*j*0.00037);
            vi0->push_back(i*i*j);
        }

#ifdef TEST_VECTORS
        m_treeWrapper.Set<FVEC*>( "testVectorTree", "vf0", vf0 );
        m_treeWrapper.Set<DVEC*>( "testVectorTree", "vd0", vd0 );
        m_treeWrapper.Set<IVEC*>( "testVectorTree", "vi0", vi0 );
#endif

        m_treeWrapper.Fill( "testTree" );
#ifdef TEST_VECTORS
        m_treeWrapper.Fill( "testVectorTree" );
#endif
    }

    m_treeWrapper.Print("testTree");
#ifdef TEST_VECTORS
    m_treeWrapper.Print("testVectorTree");
//    m_treeWrapper.Scan("testVectorTree");

#endif




    std::cout << "--- TEST : Monitoring/TTreeWrapper | END   ----------------------------------" << std::endl;



//     std::cout << "--- TEST : MCManager | START ----------------------------------" << std::endl;
//     pandora::TestMCManager* testMcManager = new pandora::TestMCManager();
//     testMcManager->Test_All();

//     delete testMcManager;
//     std::cout << "--- TEST : MCManager | END ----------------------------------" << std::endl;

//     std::cout << "--- TEST : CaloHitManager | START ----------------------------------" << std::endl;
//     pandora::TestCaloHitManager* testCaloHitManager = new pandora::TestCaloHitManager();
//     testCaloHitManager->Test_All();

//     delete testCaloHitManager;
//     std::cout << "--- TEST : CaloHitManager | END ----------------------------------" << std::endl;

    std::cout << "--- TEST : Miscellaneous | START ----------------------------------" << std::endl;
    pandora::TestMiscellaneous* testMiscellaneous = new pandora::TestMiscellaneous();
    testMiscellaneous->Test_All();
    delete testMiscellaneous;
    std::cout << "--- TEST : Miscellaneous | END ----------------------------------" << std::endl;



    pandora::PhotonIDLikelihoodCalculator* plc = pandora::PhotonIDLikelihoodCalculator::Instance();
    plc->rmsSig.Fill(3.3,2.2,1.1);
   
}
