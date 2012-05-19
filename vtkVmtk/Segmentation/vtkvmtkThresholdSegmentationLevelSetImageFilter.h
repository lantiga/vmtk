/*=========================================================================

Program:   VMTK
Module:    $RCSfile: vtkvmtkThresholdSegmentationLevelSetImageFilter.h,v $
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

// .NAME vtkvmtkThresholdSegmentationLevelSetImageFilter - Wrapper class around itk::ThresholdSegmentationLevelSetImageFilter
// .SECTION Description
// vtkvmtkThresholdSegmentationLevelSetImageFilter


#ifndef __vtkvmtkThresholdSegmentationLevelSetImageFilter_h
#define __vtkvmtkThresholdSegmentationLevelSetImageFilter_h


#include "vtkSimpleImageToImageFilter.h"
#include "vtkImageData.h"
#include "vtkvmtkWin32Header.h"

class VTK_VMTK_SEGMENTATION_EXPORT vtkvmtkThresholdSegmentationLevelSetImageFilter : public vtkSimpleImageToImageFilter
{
 public:
  static vtkvmtkThresholdSegmentationLevelSetImageFilter *New();
  vtkTypeRevisionMacro(vtkvmtkThresholdSegmentationLevelSetImageFilter, vtkSimpleImageToImageFilter);

  vtkSetMacro(UpperThreshold,float);
  vtkGetMacro(UpperThreshold,float);

  vtkSetMacro(LowerThreshold,float);
  vtkGetMacro(LowerThreshold,float);

  vtkSetMacro(EdgeWeight,float);
  vtkGetMacro(EdgeWeight,float);

  vtkSetMacro(SmoothingIterations,int);
  vtkGetMacro(SmoothingIterations,int);

  vtkSetMacro(SmoothingTimeStep,float);
  vtkGetMacro(SmoothingTimeStep,float);

  vtkSetMacro(SmoothingConductance,float);
  vtkGetMacro(SmoothingConductance,float);

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

  vtkSetObjectMacro(FeatureImage,vtkImageData);
  vtkGetObjectMacro(FeatureImage,vtkImageData);
 
  vtkSetObjectMacro(SpeedImage,vtkImageData);
  vtkGetObjectMacro(SpeedImage,vtkImageData);
 
  vtkSetMacro(FeatureScaling,double);
  vtkGetMacro(FeatureScaling,double);
 
  vtkGetMacro(RMSChange,double);
 
  vtkGetMacro(ElapsedIterations,int);
  
protected:

  vtkvmtkThresholdSegmentationLevelSetImageFilter();
  ~vtkvmtkThresholdSegmentationLevelSetImageFilter();

  void SimpleExecute(vtkImageData *input, vtkImageData *output);

  float UpperThreshold;
  float LowerThreshold;
  float EdgeWeight;
  int SmoothingIterations;
  float SmoothingTimeStep;
  float SmoothingConductance;

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
  vtkImageData* FeatureImage;
  vtkImageData* SpeedImage;
  double FeatureScaling;
  double RMSChange;
  int ElapsedIterations;

private:
  vtkvmtkThresholdSegmentationLevelSetImageFilter(const vtkvmtkThresholdSegmentationLevelSetImageFilter&);  // Not implemented.
  void operator=(const vtkvmtkThresholdSegmentationLevelSetImageFilter&);  //
                                                                          // Not implemented
};

#endif




