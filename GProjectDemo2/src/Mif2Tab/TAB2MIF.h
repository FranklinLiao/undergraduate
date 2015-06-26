#pragma once
#include "mitab.h"
#include <ctype.h>


/**********************************************************************
 *                          Tab2Tab()
 *
 * Copy features from source dataset to a new dataset
 **********************************************************************/
int Tab2Tab(const char *pszSrcFname, const char *pszDstFname,
                   int nMaxFeatures)
{
    IMapInfoFile *poSrcFile = NULL, *poDstFile = NULL;//1
    TABFeature *poFeature;//2

	int      nFeatureId, iField, numFeatures=0;
    double dXMin, dYMin, dXMax, dYMax;

    /*---------------------------------------------------------------------
     * If there is a "micdsys.txt" in current directory then load it
     *--------------------------------------------------------------------*/
    MITABLoadCoordSysTable("micdsys.txt");

    /*---------------------------------------------------------------------
     * Try to open source file
     *--------------------------------------------------------------------*/
    if ((poSrcFile = IMapInfoFile::SmartOpen(pszSrcFname)) == NULL)
    {
        printf("Failed to open %s\n", pszSrcFname);
        return -1;
    }

    OGRFeatureDefn *poDefn = poSrcFile->GetLayerDefn();//3

    /*---------------------------------------------------------------------
     * The extension of the output filename tells us if we should create
     * a MIF or a TAB file for output.
     *--------------------------------------------------------------------*/
    if (EQUAL(".mif", pszDstFname + strlen(pszDstFname)-4) ||
        EQUAL(".mid", pszDstFname + strlen(pszDstFname)-4) )
    {
        // Create a MIF file
        poDstFile = new MIFFile;
    }
    else
    {
        /*-----------------------------------------------------------------
         * Create a TAB dataset.
         * Find out if the file contains at least 1 unique field... if so we
         * will create a TABView instead of a TABFile
         *----------------------------------------------------------------*/
        GBool    bFoundUniqueField = FALSE;
        for(iField=0; iField< poDefn->GetFieldCount(); iField++)
        {
            if (poSrcFile->IsFieldUnique(iField))
                bFoundUniqueField = TRUE;
        }

        if (bFoundUniqueField)
            poDstFile = new TABView;
        else
            poDstFile = new TABFile;
    }

    /*---------------------------------------------------------------------
     * Try to open destination file
     *--------------------------------------------------------------------*/
    if (poDstFile->Open(pszDstFname, "wb") != 0)
    {
        printf("Failed to open %s\n", pszDstFname);
        return -1;
    }

    // Pass Proj. info directly
    // TABProjInfo sProjInfo;
    // if (poSrcFile->GetProjInfo(&sProjInfo) == 0)
    //     poDstFile->SetProjInfo(&sProjInfo);

    OGRSpatialReference *poSR;//4

    poSR = poSrcFile->GetSpatialRef();
    if( poSR != NULL )
    {
        poDstFile->SetSpatialRef( poSR );
    }

    //  Set bounds (must be done after setting spatialref)
    if (poSrcFile->GetBounds(dXMin, dYMin, dXMax, dYMax) == 0)
        poDstFile->SetBounds(dXMin, dYMin, dXMax, dYMax);

    /*---------------------------------------------------------------------
     * Pass compplete fields information
     *--------------------------------------------------------------------*/
    for(iField=0; iField< poDefn->GetFieldCount(); iField++)
    {
        OGRFieldDefn *poFieldDefn = poDefn->GetFieldDefn(iField);//5

        poDstFile->AddFieldNative(poFieldDefn->GetNameRef(),
                                  poSrcFile->GetNativeFieldType(iField),
                                  poFieldDefn->GetWidth(),
                                  poFieldDefn->GetPrecision(),
                                  poSrcFile->IsFieldIndexed(iField),
                                  poSrcFile->IsFieldUnique(iField));
    }

    /*---------------------------------------------------------------------
     * Copy objects until EOF is reached
     *--------------------------------------------------------------------*/
    nFeatureId = -1;
    while ( (nFeatureId = poSrcFile->GetNextFeatureId(nFeatureId)) != -1 )
    {
        poFeature = poSrcFile->GetFeatureRef(nFeatureId);
        if (poFeature)
        {
//            poFeature->DumpReadable(stdout);
//            poFeature->DumpMIF();
            poDstFile->SetFeature(poFeature);
        }
        else
        {
            printf( "Failed to read feature %d.\n",
                    nFeatureId );
            return -1;      // GetFeatureRef() failed: Error
        }
    }

    /*---------------------------------------------------------------------
     * Cleanup and exit.
     *--------------------------------------------------------------------*/
    poDstFile->Close();
    delete poDstFile;

    poSrcFile->Close();
    delete poSrcFile;

    MITABFreeCoordSysTable();

    return 0;
}


