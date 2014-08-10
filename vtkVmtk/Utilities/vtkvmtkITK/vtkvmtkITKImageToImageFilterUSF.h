/*=========================================================================

  Copyright Brigham and Women's Hospital (BWH) All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Program:   vtkvmtkITK
  Module:    $HeadURL: http://svn.slicer.org/Slicer4/trunk/Libs/vtkvmtkITK/vtkvmtkITKImageToImageFilterUSF.h $
  Date:      $Date: 2006-12-21 07:21:52 -0500 (Thu, 21 Dec 2006) $
  Version:   $Revision: 1900 $

==========================================================================*/

#ifndef __vtkvmtkITKImageToImageFilterUSF
#define __vtkvmtkITKImageToImageFilterUSF

#include "vtkvmtkITKImageToImageFilter.h"
#include "vtkImageAlgorithm.h"
#include "itkImageToImageFilter.h"
#include "itkVTKImageExport.h"
#include "itkVTKImageImport.h"
#include "vtkvmtkITKUtility.h"


class VTK_VMTK_ITK_EXPORT vtkvmtkITKImageToImageFilterUSF : public vtkvmtkITKImageToImageFilter
{
public:
  vtkTypeMacro(vtkvmtkITKImageToImageFilterUSF,vtkvmtkITKImageToImageFilter);
  static vtkvmtkITKImageToImageFilterUSF* New() { return 0; };
  void PrintSelf(ostream& os, vtkIndent indent)
  {
    Superclass::PrintSelf ( os, indent );
    os << m_Filter;
  };

protected:

  /// To/from ITK
  typedef unsigned short InputImagePixelType;
  typedef float  OutputImagePixelType;
  typedef itk::Image<InputImagePixelType, 3> InputImageType;
  typedef itk::Image<OutputImagePixelType, 3> OutputImageType;

  typedef itk::VTKImageImport<InputImageType> ImageImportType;
  typedef itk::VTKImageExport<OutputImageType> ImageExportType;
  ImageImportType::Pointer itkImporter;
  ImageExportType::Pointer itkExporter;

  typedef itk::ImageToImageFilter<InputImageType,OutputImageType> GenericFilterType;
  GenericFilterType::Pointer m_Filter;

  vtkvmtkITKImageToImageFilterUSF ( GenericFilterType* filter )
  {
    /// Need an import, export, and a ITK pipeline
    m_Filter = filter;
    this->itkImporter = ImageImportType::New();
    this->itkExporter = ImageExportType::New();
    ConnectPipelines(this->vtkExporter, this->itkImporter);
    ConnectPipelines(this->itkExporter, this->vtkImporter);
    this->LinkITKProgressToVTKProgress ( m_Filter );

    /// Set up the filter pipeline
    m_Filter->SetInput ( this->itkImporter->GetOutput() );
    this->itkExporter->SetInput ( m_Filter->GetOutput() );
    this->vtkCast->SetOutputScalarTypeToUnsignedShort();
  };

  ~vtkvmtkITKImageToImageFilterUSF()
  {
  };

private:
  vtkvmtkITKImageToImageFilterUSF(const vtkvmtkITKImageToImageFilterUSF&);  /// Not implemented.
  void operator=(const vtkvmtkITKImageToImageFilterUSF&);  /// Not implemented.
};

#endif
