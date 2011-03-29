/**
 *  @file   TestPandora/src/PandoraInterface.cc
 * 
 *  @brief  Implementation for the pandora interface binary
 * 
 *  $Log: $
 */

#include "Api/PandoraApi.h"

#include "FineGranularityContent.h"
#include "KMeansContent.h"

#include "SimpleBFieldCalculator.h"

#include <iostream>

static pandora::Pandora *m_pPandora;

int main(int argc, const char *argv[])
{
    try
    {
        // Parse command line
        const int nArgs(argc - 1);

        if ((nArgs < 1) || (nArgs > 2))
        {
            std::cout << std::endl << "Usage: ./PandoraInterface PandoraSettings.xml [nEventsToProcess]" << std::endl << std::endl;
            return 1;
        }

        // Construct pandora instance
        m_pPandora = new pandora::Pandora();

        // Register content from external pandora libraries
        PANDORA_THROW_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, PandoraApi::SetPseudoLayerCalculator(*m_pPandora,
            new FineGranularityPseudoLayerCalculator()));

        PANDORA_THROW_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, PandoraApi::SetShowerProfileCalculator(*m_pPandora,
            new FineGranularityShowerProfileCalculator()));

        PANDORA_THROW_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, FineGranularityContent::RegisterAlgorithms(*m_pPandora));
        PANDORA_THROW_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, FineGranularityContent::RegisterHelperFunctions(*m_pPandora));
        PANDORA_THROW_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, KMeansContent::RegisterAlgorithms(*m_pPandora));

        // Register local content
        PANDORA_THROW_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, PandoraApi::SetBFieldCalculator(*m_pPandora,
            new SimpleBFieldCalculator()));

        // Read in the PandoraSettings
        const std::string settingsFile(argv[1]);
        PANDORA_THROW_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, PandoraApi::ReadSettings(*m_pPandora, settingsFile));

        // Process the events
        const int nEventsToProcess((nArgs == 2) ? atoi(argv[2]) : -1);
        int nEvents(0);

        while ((nEvents++ < nEventsToProcess) || (0 > nEventsToProcess))
        {
            PANDORA_THROW_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, PandoraApi::ProcessEvent(*m_pPandora));
            PANDORA_THROW_RESULT_IF(pandora::STATUS_CODE_SUCCESS, !=, PandoraApi::Reset(*m_pPandora));
        }
    }
    catch (pandora::StatusCodeException &statusCodeException)
    {
        std::cerr << "Pandora Exception caught: " << statusCodeException.ToString() << std::endl;
        return 1;
    }

    return 0;
}
