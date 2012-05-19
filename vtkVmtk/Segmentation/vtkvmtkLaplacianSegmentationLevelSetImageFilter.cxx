/*=========================================================================

Program:   VMTK
Module:    $RCSfile: vtkbvsLaplacianSegmentationLevelSetImageFilter.cxx,v $
Language:  C++
Date:      $Date: 2006/04/06 16:48:25 $
Version:   $Revision: 1.1 $

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

#include "vtkvmtkLaplacianSegmentationLevelSetImageFilter.h"
#include "vtkImageData.h"
#include "vtkObjectFactory.h"

#include "vtkvmtkITKFilterUtilities.h"

#include "itkLaplacianSegmentationLevelSetImageFilter.h"

vtkCxxRevisionMacro(vtkvmtkLaplacianSegmentationLevelSetImageFilter, "$Revision: 1.4 $");
vtkStandardNewMacro(vtkvmtkLaplacianSegmentationLevelSetImageFilter);

vtkvmtkLaplacianSegmentationLevelSetImageFilter::vtkvmtkLaplacianSegmentationLevelSetImageFilter()
{
  this->IsoSurfaceValue = 0.0;
  this->NumberOfIterations = 0;
  this->PropagationScaling = 1.0;
  this->CurvatureScaling = 0.0;
  this->MaximumRMSError = 0.0;
  this->UseNegativeFeatures = 0;
  this->UseImageSpacing = 1;
  this->InterpolateSurfaceLocation = 1;
  this->FeatureImage = NULL;
  this->SpeedImage = NULL;
  this->FeatureScaling = 1.0;
  this->RMSChange = 0.0;
  this->ElapsedIterations = 0;
}

vtkvmtkLaplacianSegmentationLevelSetImageFilter::~vtkvmtkLaplacianSegmentationLevelSetImageFilter()
{
  if (this->FeatureImage)
    {
    this->FeatureImage->Delete();
    this->FeatureImage = NULL;
    }
  if (this->SpeedImage)
    {
    this->SpeedImage->Delete();
    this->SpeedImage = NULL;
    }
}

void vtkvmtkLaplacianSegmentationLevelSetImageFilter::SimpleExecute(vtkImageData *input, vtkImageData *output)
{
  typedef itk::Image<float,3> ImageType;

  ImageType::Pointer inImage = ImageType::New();
  ImageType::Pointer featureImage = ImageType::New();
  ImageType::Pointer speedImage = ImageType::New();

  vtkvmtkITKFilterUtilities::VTKToITKImage<ImageType>(input,inImage);
  vtkvmtkITKFilterUtilities::VTKToITKImage<ImageType>(this->FeatureImage,featureImage);
  vtkvmtkITKFilterUtilities::VTKToITKImage<ImageType>(this->SpeedImage,speedImage);

  typedef itk::LaplacianSegmentationLevelSetImageFilter<ImageType,ImageType> ImageFilterType;

  ImageFilterType::Pointer imageFilter = ImageFilterType::New();
  imageFilter->SetInput(inImage);
  imageFilter->SetIsoSurfaceValue(this->IsoSurfaceValue);
  imageFilter->SetNumberOfIterations(this->NumberOfIterations);
  imageFilter->SetPropagationScaling(this->PropagationScaling);
  imageFilter->SetCurvatureScaling(this->CurvatureScaling);
  imageFilter->SetMaximumRMSError(this->MaximumRMSError);
  imageFilter->SetUseNegativeFeatures(this->UseNegativeFeatures);
  imageFilter->SetUseImageSpacing(this->UseImageSpacing);
  imageFilter->SetInterpolateSurfaceLocation(this->InterpolateSurfaceLocation);
  imageFilter->SetFeatureImage(featureImage);
  imageFilter->SetSpeedImage(speedImage);
  imageFilter->SetFeatureScaling(this->FeatureScaling);
  imageFilter->Update();

  this->RMSChange = imageFilter->GetRMSChange();
  this->ElapsedIterations = imageFilter->GetElapsedIterations();

  vtkvmtkITKFilterUtilities::ITKToVTKImage<ImageType>(imageFilter->GetOutput(),output);
}



