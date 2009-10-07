/**
 *    @file    PandoraPFANew/include/Test/TestTrackManager.h
 * 
 *    @brief    Header file for the TrackManager test-class.
 * 
 *    $Log: $
 */
#ifndef TEST_TRACK_MANAGER_H
#define TEST_TRACK_MANAGER_H 1

#include "Pandora/PandoraInternal.h"

#include "StatusCodes.h"

#include <assert.h>

namespace pandora
{

/**
 *    @brief TestTrackManager class
 */
class TestTrackManager
{
public:
    /**
     *  @brief  test the GetMCParticle method
     */
     StatusCode Test_CreateTrack();
   
    /**
     *  @brief  test the matching of tracks to their correct mc particles for particle flow
     */
    StatusCode Test_MatchTracksToMCPfoTargets();

    /**
     *  @brief  Reset the calo hit manager
     */
    StatusCode Test_Reset();

    /**
     *  @brief  combined tests
     */
     StatusCode Test_Combined();

    /**
     *  @brief  Run all tests
     */
     StatusCode Test_All();


    // helper functions for debugging

    /**
     *  @brief  prints the data members of the TrackManager (sizes, initialization state, ...)
     *
     *  @param  pPandora Pandora object of which the mc particle trees are printed
     *  @param  o the output stream to which everything is printed
     */
    static void PrintTrackManagerData(const Pandora &pPandora, std::ostream & o);

};

} // namespace pandora

#endif // #ifndef TEST_TRACK_MANAGER_H
