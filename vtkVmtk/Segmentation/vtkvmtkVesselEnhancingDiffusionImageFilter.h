/*=========================================================================

Program:   VMTK
Module:    $RCSfile: vtkvmtkVesselEnhancingDiffusionImageFilter.h,v $
Language:  C++
Date:      $Date: 2006/04/06 16:48:25 $
Version:   $Revision: 1.2 $

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

// .NAME vtkvmtkVesselEnhancingDiffusionImageFilter - Wrapper class around itk::VesselEnhancingDiffusionImageFilter
// .SECTION Description
// vtkvmtkVesselEnhancingDiffusionImageFilter


#ifndef __vtkvmtkVesselEnhancingDiffusionImageFilter_h
#define __vtkvmtkVesselEnhancingDiffusionImageFilter_h

#include "vtkSimpleImageToImageFilter.h"
#include "vtkvmtkWin32Header.h"

class VTK_VMTK_SEGMENTATION_EXPORT vtkvmtkVesselEnhancingDiffusionImageFilter : public vtkSimpleImageToImageFilter
{
 public:
  static vtkvmtkVesselEnhancingDiffusionImageFilter *New();
  vtkTypeRevisionMacro(vtkvmtkVesselEnhancingDiffusionImageFilter, vtkSimpleImageToImageFilter);

  vtkSetMacro(SigmaMin,double);
  vtkGetMacro(SigmaMin,double);

  vtkSetMacro(SigmaMax,double);
  vtkGetMacro(SigmaMax,double);

  vtkSetMacro(NumberOfSigmaSteps,int);
  vtkGetMacro(NumberOfSigmaSteps,int);

  vtkGetMacro(SigmaStepMethod,int);
  vtkSetMacro(SigmaStepMethod,int);
  void SetSigmaStepMethodToEquispaced()
  {
    this->SetSigmaStepMethod(EQUISPACED);
  }
  
  void SetSigmaStepMethodToLogarithmic()
  {
    this->SetSigmaStepMethod(LOGARITHMIC);
  }

  vtkSetMacro(TimeStep,double);
  vtkGetMacro(TimeStep,double);

  vtkSetMacro(Epsilon,double);
  vtkGetMacro(Epsilon,double);

  vtkSetMacro(WStrength,double);
  vtkGetMacro(WStrength,double);

  vtkSetMacro(Sensitivity,double);
  vtkGetMacro(Sensitivity,double);

  vtkSetMacro(NumberOfIterations,int);
  vtkGetMacro(NumberOfIterations,int);

  vtkSetMacro(Alpha,double);
  vtkGetMacro(Alpha,double);

  vtkSetMacro(Beta,double);
  vtkGetMacro(Beta,double);

  vtkSetMacro(Gamma,double);
  vtkGetMacro(Gamma,double);

  vtkSetMacro(C,double);
  vtkGetMacro(C,double);

  vtkSetMacro(NumberOfDiffusionSubIterations,int);
  vtkGetMacro(NumberOfDiffusionSubIterations,int);

//BTX
  enum
  {
    EQUISPACED,
    LOGARITHMIC
  };
//ETX

protected:
  vtkvmtkVesselEnhancingDiffusionImageFilter(); 
  ~vtkvmtkVesselEnhancingDiffusionImageFilter(); 

  void SimpleExecute(vtkImageData *input, vtkImageData *output);

  double SigmaMin;
  double SigmaMax;
  int NumberOfSigmaSteps;
  int SigmaStepMethod;

  double TimeStep;
  double Epsilon;
  double WStrength;
  double Sensitivity;
  int NumberOfIterations;
  double Alpha;
  double Beta;
  double Gamma;
  double C;
  int NumberOfDiffusionSubIterations;

private:
  vtkvmtkVesselEnhancingDiffusionImageFilter(const vtkvmtkVesselEnhancingDiffusionImageFilter&);  // Not implemented.
  void operator=(const vtkvmtkVesselEnhancingDiffusionImageFilter&);  // Not implemented.
};


/*
#include "vtkvmtkITKImageToImageFilterFF.h"
#include "itkAnisotropicDiffusionVesselEnhancementImageFilter.h"
#include "itkMultiScaleHessianBasedMeasureImageFilter.h"
#include "itkHessianSmoothed3DToVesselnessMeasureImageFilter.h"
#include "vtkvmtkWin32Header.h"

class VTK_VMTK_SEGMENTATION_EXPORT vtkvmtkVesselEnhancingDiffusionImageFilter : public vtkvmtkITKImageToImageFilterFF
{
 public:
  static vtkvmtkVesselEnhancingDiffusionImageFilter *New();
  vtkTypeRevisionMacro(vtkvmtkVesselEnhancingDiffusionImageFilter, vtkvmtkITKImageToImageFilterFF);

  void SetSigmaMin(double value)
  {
    DelegateITKInputMacro(GetMultiScaleVesselnessFilter()->SetSigmaMinimum,value);
  }

  double GetSigmaMin()
  {
    DelegateITKOutputMacro(GetMultiScaleVesselnessFilter()->GetSigmaMinimum);
  }

  void SetSigmaMax(double value)
  {
    DelegateITKInputMacro(GetMultiScaleVesselnessFilter()->SetSigmaMaximum,value);
  }

  double GetSigmaMax()
  {
    DelegateITKOutputMacro(GetMultiScaleVesselnessFilter()->GetSigmaMaximum);
  }

  void SetNumberOfSigmaSteps(int value)
  {
    DelegateITKInputMacro(GetMultiScaleVesselnessFilter()->SetNumberOfSigmaSteps,value);
  }

  int GetNumberOfSigmaSteps()
  {
    DelegateITKOutputMacro(GetMultiScaleVesselnessFilter()->GetNumberOfSigmaSteps);
  }

  void SetSigmaStepMethodToEquispaced()
  {
    this->GetImageFilterPointer()->GetMultiScaleVesselnessFilter()->SetSigmaStepMethodToEquispaced();
    this->Modified();
  }
  
  void SetSigmaStepMethodToLogarithmic()
  {
    this->GetImageFilterPointer()->GetMultiScaleVesselnessFilter()->SetSigmaStepMethodToLogarithmic();
    this->Modified();
  }

  void SetTimeStep(double value)
  {
    DelegateITKInputMacro(SetTimeStep,value);
  }

  double GetTimeStep()
  {
    DelegateITKOutputMacro(GetTimeStep);
  }

  void SetEpsilon(double value)
  {
    DelegateITKInputMacro(SetEpsilon,value);
  }

  double GetEpsilon()
  {
    DelegateITKOutputMacro(GetEpsilon);
  }

  void SetWStrength(double value)
  {
    DelegateITKInputMacro(SetWStrength,value);
  }

  double GetWStrength()
  {
    DelegateITKOutputMacro(GetWStrength);
  }

  void SetSensitivity(double value)
  {
    DelegateITKInputMacro(SetSensitivity,value);
  }

  double GetSensitivity()
  {
    DelegateITKOutputMacro(GetSensitivity);
  }

  void SetNumberOfIterations(int value)
  {
    DelegateITKInputMacro(SetNumberOfIterations,value);
  }

  int GetNumberOfIterations()
  {
    DelegateITKOutputMacro(GetNumberOfIterations);
  }

  void SetAlpha(double value)
  {
    ImageFilterType* tempFilter = dynamic_cast<ImageFilterType*>(this->m_Filter.GetPointer()); 
    if (tempFilter) 
      { 
      dynamic_cast<VesselnessFilterType*>(tempFilter->GetMultiScaleVesselnessFilter()->GetHessianToMeasureFilter())->SetAlpha(value); 
      this->Modified(); 
      }
  }

  double GetAlpha()
  {
    ImageFilterType* tempFilter = dynamic_cast<ImageFilterType*>(this->m_Filter.GetPointer()); 
    if (tempFilter) 
      { 
      return dynamic_cast<VesselnessFilterType*>(tempFilter->GetMultiScaleVesselnessFilter()->GetHessianToMeasureFilter())->GetAlpha(); 
      }
    else
      {
      vtkErrorMacro ( << this->GetClassName() << " Error getting method. Dynamic cast returned 0" );
      return 0.0;
      }
  }

  void SetBeta(double value)
  {
    ImageFilterType* tempFilter = dynamic_cast<ImageFilterType*>(this->m_Filter.GetPointer()); 
    if (tempFilter) 
      { 
      dynamic_cast<VesselnessFilterType*>(tempFilter->GetMultiScaleVesselnessFilter()->GetHessianToMeasureFilter())->SetBeta(value); 
      this->Modified(); 
      }
  }

  double GetBeta()
  {
    ImageFilterType* tempFilter = dynamic_cast<ImageFilterType*>(this->m_Filter.GetPointer()); 
    if (tempFilter) 
      { 
      return dynamic_cast<VesselnessFilterType*>(tempFilter->GetMultiScaleVesselnessFilter()->GetHessianToMeasureFilter())->GetBeta(); 
      }
    else
      {
      vtkErrorMacro ( << this->GetClassName() << " Error getting method. Dynamic cast returned 0" );
      return 0.0;
      }
  }

  void SetGamma(double value)
  {
    ImageFilterType* tempFilter = dynamic_cast<ImageFilterType*>(this->m_Filter.GetPointer()); 
    if (tempFilter) 
      { 
      dynamic_cast<VesselnessFilterType*>(tempFilter->GetMultiScaleVesselnessFilter()->GetHessianToMeasureFilter())->SetGamma(value); 
      this->Modified(); 
      }
  }

  double GetGamma()
  {
    ImageFilterType* tempFilter = dynamic_cast<ImageFilterType*>(this->m_Filter.GetPointer()); 
    if (tempFilter) 
      { 
      return dynamic_cast<VesselnessFilterType*>(tempFilter->GetMultiScaleVesselnessFilter()->GetHessianToMeasureFilter())->GetGamma(); 
      }
    else
      {
      vtkErrorMacro ( << this->GetClassName() << " Error getting method. Dynamic cast returned 0" );
      return 0.0;
      }
  }

  void SetC(double value)
  {
    ImageFilterType* tempFilter = dynamic_cast<ImageFilterType*>(this->m_Filter.GetPointer()); 
    if (tempFilter) 
      { 
      dynamic_cast<VesselnessFilterType*>(tempFilter->GetMultiScaleVesselnessFilter()->GetHessianToMeasureFilter())->SetC(value); 
      this->Modified(); 
      }
  }

  double GetC()
  {
    ImageFilterType* tempFilter = dynamic_cast<ImageFilterType*>(this->m_Filter.GetPointer()); 
    if (tempFilter) 
      { 
      return dynamic_cast<VesselnessFilterType*>(tempFilter->GetMultiScaleVesselnessFilter()->GetHessianToMeasureFilter())->GetC(); 
      }
    else
      {
      vtkErrorMacro ( << this->GetClassName() << " Error getting method. Dynamic cast returned 0" );
      return 0.0;
      }
  }

  void SetNumberOfDiffusionSubIterations(int value)
  {
    DelegateITKInputMacro(SetNumberOfDiffusionSubIterations,value);
  }

  int GetNumberOfDiffusionSubIterations()
  {
    DelegateITKOutputMacro(GetNumberOfDiffusionSubIterations);
  }

protected:
  //BTX
  typedef itk::AnisotropicDiffusionVesselEnhancementImageFilter<Superclass::InputImageType, Superclass::OutputImageType> ImageFilterType;
  typedef ImageFilterType::VesselnessFilterType VesselnessFilterType;

  vtkvmtkVesselEnhancingDiffusionImageFilter() : Superclass(ImageFilterType::New())
  {
    ImageFilterType* imageFilter = this->GetImageFilterPointer();
    imageFilter->GetMultiScaleVesselnessFilter()->SetSigmaStepMethodToEquispaced();
  }

  ~vtkvmtkVesselEnhancingDiffusionImageFilter() {};
  ImageFilterType* GetImageFilterPointer() { return dynamic_cast<ImageFilterType*>(m_Filter.GetPointer()); }
  //ETX

private:
  vtkvmtkVesselEnhancingDiffusionImageFilter(const vtkvmtkVesselEnhancingDiffusionImageFilter&);  // Not implemented.
  void operator=(const vtkvmtkVesselEnhancingDiffusionImageFilter&);  // Not implemented.
};
*/
#endif

