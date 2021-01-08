/*!
 * \file CFEMStandardLineAdjacentQuadSol.hpp
 * \brief Class for the FEM standard surface line element
 *        adjacent to a quadrilateral for the solution.
 *        The functions are in the <i>CFEMStandardLineAdjacentQuadSol.cpp</i> file.
 * \author E. van der Weide
 * \version 7.0.8 "Blackbird"
 *
 * SU2 Project Website: https://su2code.github.io
 *
 * The SU2 Project is maintained by the SU2 Foundation
 * (http://su2foundation.org)
 *
 * Copyright 2012-2020, SU2 Contributors (cf. AUTHORS.md)
 *
 * SU2 is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * SU2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with SU2. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once 

#include "CFEMStandardQuadBase.hpp"
#include "CGemmBase.hpp"

/*!
 * \class CFEMStandardLineAdjacentQuadSol.
 * \brief Class which defines the variables and methods for the line
 *        standard surface element adjacent to a quadrilateral for the solution.
 * \author E. van der Weide
 * \version 7.0.8 "Blackbird"
 */
class CFEMStandardLineAdjacentQuadSol final: public CFEMStandardQuadBase {

public:
  /*!
   * \brief Default constructor of the class, deleted to make sure the
   *        overloaded constructor is always used.
   */
  CFEMStandardLineAdjacentQuadSol() = delete;

  /*!
   * \overload
   * \param[in] val_nPoly       - Polynomial degree of the grid for this element.
   * \param[in] val_orderExact  - Polynomial degree that must be integrated exactly.
   * \param[in] val_faceID_Elem - This is the face ID of the adjacent volume element
   *                              to which this surface element corresponds.
   * \param[in] val_orientation - Orientation of this surface element relative to
   *                              the adjacent volume element.
   * \param[in] val_gemm_1      - Pointer to the gemm type used to carry out the
   *                              first gemm functionality for this standard face.
   * \param[in] val_gemm_2      - Pointer to the gemm type used to carry out the
   *                              second gemm functionality for this standard face.
   */
  CFEMStandardLineAdjacentQuadSol(const unsigned short val_nPoly,
                                  const unsigned short val_orderExact,
                                  const unsigned short val_faceID_Elem,
                                  const unsigned short val_orientation,
                                  CGemmBase           *val_gemm_1,
                                  CGemmBase           *val_gemm_2);

  /*!
   * \brief Destructor. Nothing to be done.
   */
  ~CFEMStandardLineAdjacentQuadSol() = default;

private:

  unsigned short faceID_Elem;   /*!< \brief Face ID of the adjacent quad, which corresponds to this face. */
  unsigned short orientation;   /*!< \brief Orientation of this face relative to the adjacent quad. */

  CGemmBase *gemmDOFs2Int = nullptr; /*!< \brief Pointer to the gemm type used to to compute the data in the
                                                 integration points of the face from the volume DOFs. */
  CGemmBase *gemmInt2DOFs = nullptr; /*!< \brief Pointer to the gemm type used to to compute the data in the
                                                 volume DOFs from the integration points of the face. */

  vector<ColMajorMatrix<passivedouble> > tensorSol;     /*!< \brief The two 1D components of the tensor to compute
                                                                    the solution on the face of the quad. */
  vector<ColMajorMatrix<passivedouble> > tensorDSolDr;  /*!< \brief The two 1D components of the tensor to compute
                                                                    the derivative in r-direction of the solution
                                                                    on the face of the quad. */
  vector<ColMajorMatrix<passivedouble> > tensorDSolDs;  /*!< \brief The two 1D components of the tensor to compute
                                                                    the derivative in s-direction of the solution
                                                                    on the face of the quad. */
};