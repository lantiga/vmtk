/*=========================================================================

Program:   VMTK
Module:    $RCSfile: vtkvmtkGeodesicActiveContourLevelSet2DImageFilter.h,v $
Language:  C++
Date:      $Date: 2006/04/06 16:48:25 $
Version:   $Revision: 1.4 $

  Copyright (c) Luca Antiga, David Steinman. All rights reserved.
  See LICENCE file for details.

  Portions of this code are covered under the VTK copyright.
  See VTKCopyright.txt or http://www.kitware.com/VTKCopyright.htm 
  for details.

  Portions of this code are covered under the ITK copyright.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm
  for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

// .NAME vtkvmtkGeodesicActiveContourLevelSet2DImageFilter - Wrapper class around itk::GeodesicActiveContourLevelSetImageFilter
// .SECTION Description
// vtkvmtkGeodesicActiveContourLevelSet2DImageFilter


#ifndef __vtkvmtkGeodesicActiveContourLevelSet2DImageFilter_h
#define __vtkvmtkGeodesicActiveContourLevelSet2DImageFilter_h


#include "vtkSimpleImageToImageFilter.h"
#include "vtkImageData.h"
#include "vtkvmtkWin32Header.h"

class VTK_VMTK_SEGMENTATION_EXPORT vtkvmtkGeodesicActiveContourLevelSet2DImageFilter : public vtkSimpleImageToImageFilter
{
 public:
  static vtkvmtkGeodesicActiveContourLevelSet2DImageFilter *New();
  vtkTypeRevisionMacro(vtkvmtkGeodesicActiveContourLevelSet2DImageFilter, vtkSimpleImageToImageFilter);

  vtkSetMacro(IsoSurfaceValue,double);
  vtkGetMacro(IsoSurfaceValue,double);
 
  vtkSetMacro(NumberOfIterations,int);
  vtkGetMacro(NumberOfIterations,int);
  
  vtkSetMacro(PropagationScaling,double);
  vtkGetMacro(PropagationScaling,double);

  vtkSetMacro(CurvatureScaling,double);
  vtkGetMacro(CurvatureScaling,double);

  vtkSetMacro(AdvectionScaling,double);
  vtkGetMacro(AdvectionScaling,double);
 
  vtkSetMacro(MaximumRMSError,double);
  vtkGetMacro(MaximumRMSError,double);
 
  vtkSetMacro(UseNegativeFeatures,int);
  vtkGetMacro(UseNegativeFeatures,int);
  vtkBooleanMacro(UseNegativeFeatures,int);
 
  vtkSetMacro(UseImageSpacing,int);
  vtkGetMacro(UseImageSpacing,int);
  vtkBooleanMacro(UseImageSpacing,int);

  vtkSetMacro(AutoGenerateSpeedAdvection,int);
  vtkGetMacro(AutoGenerateSpeedAdvection,int);
  vtkBooleanMacro(AutoGenerateSpeedAdvection,int);

  vtkSetMacro(InterpolateSurfaceLocation,int);
  vtkGetMacro(InterpolateSurfaceLocation,int);
  vtkBooleanMacro(InterpolateSurfaceLocation,int);

  vtkSetMacro(DerivativeSigma,double);
  vtkGetMacro(DerivativeSigma,double);
 
  vtkSetObjectMacro(FeatureImage,vtkImageData);
  vtkGetObjectMacro(FeatureImage,vtkImageData);
 
  vtkSetObjectMacro(SpeedImage,vtkImageData);
  vtkGetObjectMacro(SpeedImage,vtkImageData);
 
  vtkSetMacro(FeatureScaling,double);
  vtkGetMacro(FeatureScaling,double);
 
  vtkGetMacro(RMSChange,double);
 
  vtkGetMacro(ElapsedIterations,int);
 
    
protected:
  vtkvmtkGeodesicActiveContourLevelSet2DImageFilter();
  ~vtkvmtkGeodesicActiveContourLevelSet2DImageFilter();

  void SimpleExecute(vtkImageData *input, vtkImageData *output);

   double IsoSurfaceValue;
  int NumberOfIterations;
  double PropagationScaling;
  double CurvatureScaling;
  double AdvectionScaling;
  double MaximumRMSError;
  int UseNegativeFeatures;
  int UseImageSpacing;
  int AutoGenerateSpeedAdvection;
  int InterpolateSurfaceLocation;
  double DerivativeSigma;
  vtkImageData* FeatureImage;
  vtkImageData* SpeedImage;
  double FeatureScaling;
  double RMSChange;
  int ElapsedIterations;

private:
  vtkvmtkGeodesicActiveContourLevelSet2DImageFilter(const vtkvmtkGeodesicActiveContourLevelSet2DImageFilter&);  // Not implemented.
  void operator=(const vtkvmtkGeodesicActiveContourLevelSet2DImageFilter&);  //
                                                                          // Not implemented
  
};

#endif




