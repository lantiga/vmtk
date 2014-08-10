#!/usr/bin/env python

## Program:   VMTK
## Module:    $RCSfile: vmtksurfacecenterlineprojection.py,v $
## Language:  Python
## Date:      $Date: 2005/09/14 09:48:31 $
## Version:   $Revision: 1.5 $

##   Copyright (c) Luca Antiga, David Steinman. All rights reserved.
##   See LICENCE file for details.

##      This software is distributed WITHOUT ANY WARRANTY; without even 
##      the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
##      PURPOSE.  See the above copyright notices for more information.


import vtk
import vtkvmtk
import sys

import pypes

vmtksurfacecenterlineprojection = 'vmtkSurfaceCenterlineProjection'

class vmtkSurfaceCenterlineProjection(pypes.pypeScript):

    def __init__(self):

        pypes.pypeScript.__init__(self)
        
        self.Surface = None
        self.Centerlines = None
        self.UseRadiusInformation = 0
        self.RadiusArrayName = ''
        
        self.SetScriptName('vmtksurfacecenterlineprojection')
        self.SetInputMembers([
            ['Surface','i','vtkPolyData',1,'','','vmtksurfacereader'],
            ['Centerlines','centerlines','vtkPolyData',1,'','','vmtksurfacereader'],
            ['UseRadiusInformation','useradius','bool',1],
            ['RadiusArrayName','radiusarray','str',1]
            ])
        self.SetOutputMembers([
            ['Surface','o','vtkPolyData',1,'','','vmtksurfacewriter']
            ])

    def Execute(self):

        if self.Surface == None:
            self.PrintError('Error: No input surface.')

        if self.Centerlines == None:
            self.PrintError('Error: No input centerlines.')

        projectionFilter = vtkvmtk.vtkvmtkPolyDataCenterlineProjection()
        projectionFilter.SetInputData(self.Surface)
        projectionFilter.SetCenterlines(self.Centerlines)
        projectionFilter.SetUseRadiusInformation(self.UseRadiusInformation)
        projectionFilter.SetCenterlineRadiusArrayName(self.RadiusArrayName)
        projectionFilter.Update()

        self.Surface = projectionFilter.GetOutputData()


if __name__=='__main__':

    main = pypes.pypeMain()
    main.Arguments = sys.argv
    main.Execute()
