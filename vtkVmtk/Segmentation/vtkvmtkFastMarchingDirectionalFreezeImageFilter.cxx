/*=========================================================================

Program:   VMTK
Module:    $RCSfile: vtkvmtkFastMarchingDirectionalFreezeImageFilter.cxx,v $
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

#include "vtkvmtkFastMarchingDirectionalFreezeImageFilter.h"
#include "vtkImageData.h"
#include "vtkObjectFactory.h"

#include "vtkvmtkITKFilterUtilities.h"

#include "itkFastMarchingDirectionalFreezeImageFilter.h"

vtkCxxRevisionMacro(vtkvmtkFastMarchingDirectionalFreezeImageFilter, "$Revision: 1.4 $");
vtkStandardNewMacro(vtkvmtkFastMarchingDirectionalFreezeImageFilter);

vtkvmtkFastMarchingDirectionalFreezeImageFilter::vtkvmtkFastMarchingDirectionalFreezeImageFilter() 
{
  this->GenerateGradientImage = 1;
  this->TargetReachedMode = ALL_TARGETS;
  this->TargetValue = 0.0;
  this->TargetOffset = 0.0;
  this->Seeds = NULL;
  this->Targets = NULL;
}

vtkvmtkFastMarchingDirectionalFreezeImageFilter::~vtkvmtkFastMarchingDirectionalFreezeImageFilter() 
{
  if (this->Seeds)
    {
    this->Seeds->Delete();
    this->Seeds = NULL;
    }
  if (this->Targets)
    {
    this->Targets->Delete();
    this->Targets = NULL;
    }
}

void vtkvmtkFastMarchingDirectionalFreezeImageFilter::SimpleExecute(vtkImageData *input, vtkImageData *output)
{
  typedef itk::Image<float,3> ImageType;

  ImageType::Pointer inImage = ImageType::New();

  vtkvmtkITKFilterUtilities::VTKToITKImage<ImageType>(input,inImage);

  typedef itk::FastMarchingDirectionalFreezeImageFilter<ImageType,ImageType> ImageFilterType;

  ImageFilterType::Pointer imageFilter = ImageFilterType::New();

  ImageFilterType::NodeContainerPointer seeds = ImageFilterType::NodeContainer::New();

  int i;
  for (i=0; i<this->Seeds->GetNumberOfIds(); i++)                                                                                   
    {                                                                                                                                
    // TODO: here we get the point. We should get the cell center instead.                                                           
    ImageType::PointType seedPoint(input->GetPoint(this->Seeds->GetId(i)));                
    ImageFilterType::NodeType::IndexType seedIndex;                                                                                  
    inImage->TransformPhysicalPointToIndex(seedPoint,seedIndex);                                              
    ImageFilterType::PixelType seedValue = itk::NumericTraits<ImageFilterType::PixelType>::Zero;                                     
    ImageFilterType::NodeType seed;
    seed.SetValue(seedValue);                                                                                                        
    seed.SetIndex(seedIndex);                                                                                                        
    seeds->InsertElement(i,seed);
    }                                                                                                                                
  imageFilter->SetTrialPoints(seeds);                                                                             
  
  ImageFilterType::NodeContainerPointer targets = ImageFilterType::NodeContainer::New();                                              

  for (i=0; i<this->Targets->GetNumberOfIds(); i++)                                                                                   
    {
    // TODO: here we get the point. We should get the cell center instead.                                                           
    ImageType::PointType seedPoint(input->GetPoint(this->Targets->GetId(i)));                
    ImageFilterType::NodeType::IndexType seedIndex;                                                                                  
    inImage->TransformPhysicalPointToIndex(seedPoint,seedIndex);                                              
    ImageFilterType::PixelType seedValue = itk::NumericTraits<ImageFilterType::PixelType>::Zero;                                     
    ImageFilterType::NodeType seed;                                                                                                  
    seed.SetValue(seedValue);
    seed.SetIndex(seedIndex);
    targets->InsertElement(i,seed);                                                                                                   
    }                                                                                                                                
  imageFilter->SetTargetPoints(targets);                                                                             
  if (this->TargetReachedMode == ONE_TARGET) {
    imageFilter->SetTargetReachedModeToOneTarget();
  }
  else if (this->TargetReachedMode == ALL_TARGETS) {
    imageFilter->SetTargetReachedModeToAllTargets();
  }

  imageFilter->SetInput(inImage);
  imageFilter->Update();

  this->TargetValue = imageFilter->GetTargetValue();

  vtkvmtkITKFilterUtilities::ITKToVTKImage<ImageType>(imageFilter->GetOutput(),output);
}

