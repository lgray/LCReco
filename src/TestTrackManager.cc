/**
 *	@file	PandoraPFANew/src/Test/TestTrackManager.cc
 * 
 * 	@brief	Implementation of the tester for the mc manager class.
 * 
 *	$Log: $
 */

#include "Managers/TrackManager.h"
#include "Managers/MCManager.h"

#include "Objects/MCParticle.h"
#include "Objects/Track.h"

#include "TestTrackManager.h"
#include "TestMCManager.h"

#include <assert.h>
#include <iostream>
#include <iomanip>

namespace pandora
{

StatusCode TestTrackManager::Test_CreateTrack()
{
    std::cout << "--- --- CreateTrack | START ------------------------------" << std::endl;

    std::cout << "        create TrackManager" << std::endl;
    TrackManager* pTrackManager = new TrackManager();
    assert( pTrackManager != 0 ); // problem at creating a TrackManager

    std::cout << "        delete TrackManager" << std::endl;
    delete pTrackManager;
    std::cout << "--- --- CreateTrack | END ------------------------------" << std::endl;
    return STATUS_CODE_SUCCESS;
}



//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode TestTrackManager::Test_MatchTracksToMCPfoTargets()
{
    std::cout << "--- --- MatchTracksToMCPfoTargets | START ------------------------------" << std::endl;
    std::cout << "        create TrackManager" << std::endl;
    TrackManager* pTrackManager = new TrackManager();
    assert( pTrackManager != 0 ); // problem at creating a TrackManager

    std::cout << "        delete TrackManager" << std::endl;
    delete pTrackManager;
    std::cout << "--- --- MatchTracksToMCPfoTargets | END ------------------------------" << std::endl;
    return STATUS_CODE_SUCCESS;
}


//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode TestTrackManager::Test_Reset()
{
    std::cout << "--- --- Reset | START ------------------------------" << std::endl;

    std::cout << "        create TrackManager" << std::endl;
    TrackManager* pTrackManager = new TrackManager();
    assert( pTrackManager != 0 ); // problem at creating a TrackManager


    std::cout << "        delete TrackManager" << std::endl;
    delete pTrackManager;
    std::cout << "--- --- Reset | END ------------------------------" << std::endl;
    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode TestTrackManager::Test_Combined()
{
    std::cout << "--- --- Combined | START ------------------------------" << std::endl;

    std::cout << "        create TrackManager" << std::endl;
    TrackManager* pTrackManager = new TrackManager();
    assert( pTrackManager != 0 ); // problem at creating a TrackManager


    std::cout << "        delete TrackManager" << std::endl;
    delete pTrackManager;

    std::cout << "--- --- Combined | END ------------------------------" << std::endl;
    return STATUS_CODE_SUCCESS;
}

//------------------------------------------------------------------------------------------------------------------------------------------

StatusCode TestTrackManager::Test_All()
{
    std::cout << "--- --- ALL | START ------------------------------" << std::endl;
    assert( Test_CreateTrack() == STATUS_CODE_SUCCESS );
    assert( Test_MatchTracksToMCPfoTargets() == STATUS_CODE_SUCCESS );
    assert( Test_Combined() == STATUS_CODE_SUCCESS );

    std::cout << "--- --- ALL | END ------------------------------" << std::endl;
    return STATUS_CODE_SUCCESS;
}



//-- Helper functions for debugging --------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------------------------------------------

void TestTrackManager::PrintTrackManagerData(const Pandora &pPandora, std::ostream & o)
{
    TrackManager* trM = pPandora.m_pTrackManager;
    std::cout << "=== TrackManager ===============================" << std::endl;
    std::cout << "m_uidToTrackMap   ";
    std::cout << "size : " << trM->m_uidToTrackMap.size();
    int haveMCParticle = 0;
    for( TrackManager::UidToTrackMap::iterator it = trM->m_uidToTrackMap.begin(), itEnd = trM->m_uidToTrackMap.end(); it != itEnd; ++it )
    {
        if( (*it).second->m_pMCParticle != NULL ) ++haveMCParticle;
    }
    std::cout << "   have mc particle : " << haveMCParticle << std::endl;
    std::cout << "================================================" << std::endl;
}



} // namespace pandora
