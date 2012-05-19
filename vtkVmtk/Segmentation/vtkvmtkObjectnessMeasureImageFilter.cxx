/*=========================================================================

Program:   VMTK
Module:    $RCSfile: vtkbvsObjectnessMeasureImageFilter.cxx,v $
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

#include "vtkvmtkObjectnessMeasureImageFilter.h"
#include "vtkImageData.h"
#include "vtkObjectFactory.h"

#include "vtkvmtkITKFilterUtilities.h"

#include "itkMultiScaleHessianBasedMeasureImageFilter.h"
#include "itkHessianToObjectnessMeasureImageFilter.h"

vtkCxxRevisionMacro(vtkvmtkObjectnessMeasureImageFilter, "$Revision: 1.2 $");
vtkStandardNewMacro(vtkvmtkObjectnessMeasureImageFilter);

vtkvmtkObjectnessMeasureImageFilter::vtkvmtkObjectnessMeasureImageFilter()
{
  this->SigmaMin = 1.0;
  this->SigmaMax = 2.0;
  this->NumberOfSigmaSteps = 2;
  this->SetSigmaStepMethodToEquispaced();
  this->Alpha = 0.5;
  this->Beta = 0.5;
  this->Gamma = 0.5;
  this->ObjectDimension = 1;
  this->ScalesOutput = vtkImageData::New();
}

vtkvmtkObjectnessMeasureImageFilter::~vtkvmtkObjectnessMeasureImageFilter()
{
  if (this->ScalesOutput)
    {
    this->ScalesOutput->Delete();
    this->ScalesOutput = NULL;
    }
}

void vtkvmtkObjectnessMeasureImageFilter::SimpleExecute(vtkImageData *input, vtkImageData *output)
{
  typedef itk::Image<float,3> ImageType;

  ImageType::Pointer inImage = ImageType::New();

  vtkvmtkITKFilterUtilities::VTKToITKImage<ImageType>(input,inImage);

  typedef itk::SymmetricSecondRankTensor<double,3> HessianPixelType;
  typedef itk::Image<HessianPixelType,3> HessianImageType;
  typedef itk::HessianToObjectnessMeasureImageFilter<HessianImageType,ImageType> ObjectnessFilterType;
  typedef itk::MultiScaleHessianBasedMeasureImageFilter<ImageType,HessianImageType,ImageType> ImageFilterType;

  ObjectnessFilterType::Pointer objectnessFilter = ObjectnessFilterType::New();
  objectnessFilter->SetAlpha(this->Alpha);
  objectnessFilter->SetBeta(this->Beta);
  objectnessFilter->SetGamma(this->Gamma);
  objectnessFilter->SetObjectDimension(this->ObjectDimension);

  ImageFilterType::Pointer imageFilter = ImageFilterType::New();
  imageFilter->SetSigmaMinimum(this->SigmaMin);
  imageFilter->SetSigmaMaximum(this->SigmaMax);
  imageFilter->SetNumberOfSigmaSteps(this->NumberOfSigmaSteps);
  if (this->SigmaStepMethod == EQUISPACED)
    {
    imageFilter->SetSigmaStepMethodToEquispaced();
    }
  else if (this->SigmaStepMethod == LOGARITHMIC)
    {
    imageFilter->SetSigmaStepMethodToLogarithmic();
    }
  imageFilter->GenerateScalesOutputOn();
  imageFilter->SetHessianToMeasureFilter(objectnessFilter.GetPointer());

  imageFilter->SetInput(inImage);
  imageFilter->Update();

  vtkvmtkITKFilterUtilities::ITKToVTKImage<ImageType>(imageFilter->GetOutput(),output);
  vtkvmtkITKFilterUtilities::ITKToVTKImage<ImageFilterType::ScalesImageType>(imageFilter->GetScalesOutput(),this->ScalesOutput);
}

