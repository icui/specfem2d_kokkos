#ifndef JACOBIAN_H
#define JACOBIAN_H

#include "../include/kokkos_abstractions.h"

namespace jacobian {
/**
 * Jacobian namespace contains overloaded functions for serial (without Kokkos)
 * and Kokkos implementations (using team policy)
 *
 */

/**
 * @brief Compute global locations (x,z) from (xi, gamma)
 *
 * @note This function can only be called within a team policy
 *
 * @param teamMember Kokkos team policy team member
 * @param s_coorg scratch view of coorg subviewed at required element
 * @param ngnod Total number of control nodes per element
 * @param xi xi value of the point
 * @param gamma gamma value of point
 * @return std::tuple<type_real, type_real> (x,z) value for the point
 */
std::tuple<type_real, type_real>
compute_locations(const specfem::HostTeam::member_type &teamMember,
                  const specfem::HostScratchView2d<type_real> s_coorg,
                  const int ngnod, const type_real xi, const type_real gamma);

/**
 * @brief Compute global locations (x,z) from (xi, gamma)
 *
 *
 * @param coorg Global control node locations (x_a, z_a)
 * @param ngnod Total number of control nodes per element
 * @param xi xi value of the point
 * @param gamma gamma value of point
 * @return std::tuple<type_real, type_real> (x,z) value for the point
 */
std::tuple<type_real, type_real>
compute_locations(const specfem::HostView2d<type_real> coorg, const int ngnod,
                  const type_real xi, const type_real gamma);

/**
 * @brief Compute global locations (x,z) from shape function matrix calcualted
 * at (xi, gamma)
 *
 * @note This function can only be called within a team policy
 *
 * @param teamMember Kokkos team policy team member
 * @param s_coorg scratch view of coorg subviewed at required element
 * @param ngnod Total number of control nodes per element
 * @param shape2D shape function matrix calculated at (xi, gamma)
 * @return std::tuple<type_real, type_real> (x,z) value for the point
 */
std::tuple<type_real, type_real>
compute_locations(const specfem::HostTeam::member_type &teamMember,
                  const specfem::HostScratchView2d<type_real> s_coorg,
                  const int ngnod,
                  const specfem::HostView1d<type_real> shape2D);

/**
 * @brief Compute global locations (x,z) from shape function matrix calcualted
 * at (xi, gamma)
 *
 * @param coorg Global control node locations (x_a, z_a)
 * @param ngnod Total number of control nodes per element
 * @param shape2D shape function matrix calculated at (xi, gamma)
 * @return std::tuple<type_real, type_real> (x,z) value for the point
 */
std::tuple<type_real, type_real>
compute_locations(const specfem::HostView2d<type_real> coorg, const int ngnod,
                  const specfem::HostView1d<type_real> shape2D);

/**
 * @brief Compute partial derivatives at xi, gamma
 *
 * @note This function can only be called within a team policy
 *
 * @param teamMember Kokkos team policy team member
 * @param s_coorg scratch view of coorg subviewed at required element
 * @param ngnod Total number of control nodes per element
 * @param xi xi value of the point
 * @param gamma gamma value of point
 * @return std::tuple<type_real, type_real, type_real, type_real> partial
 * derivatives (dx/dxi, dx/dgamma, dz/dxi, dz/dgamma)
 */
std::tuple<type_real, type_real, type_real, type_real>
compute_partial_derivatives(const specfem::HostTeam::member_type &teamMember,
                            const specfem::HostScratchView2d<type_real> s_coorg,
                            const int ngnod, const type_real xi,
                            const type_real gamma);

/**
 * @brief Compute partial derivatives at xi, gamma
 *
 * @note This function can only be called within a team policy
 *
 * @param teamMember Kokkos team policy team member
 * @param s_coorg scratch view of coorg subviewed at required element
 * @param ngnod Total number of control nodes per element
 * @param dershape2D derivative of shape function matrix calculated at (xi,
 * gamma)
 * @return std::tuple<type_real, type_real, type_real, type_real> partial
 * derivatives (dx/dxi, dx/dgamma, dz/dxi, dz/dgamma)
 */
std::tuple<type_real, type_real, type_real, type_real>
compute_partial_derivatives(const specfem::HostTeam::member_type &teamMember,
                            const specfem::HostScratchView2d<type_real> s_coorg,
                            const int ngnod,
                            const specfem::HostView2d<type_real> dershape2D);

/**
 * @brief compute jacobian given partial derivatives at a point
 *
 * @param xxi partial derivative dx/dxi
 * @param zxi partial derivative dz/dxi
 * @param xgamma partial derivative dx/dgamma
 * @param zgamma partial derivative dz/dgamma
 * @return type_real computed jacobian
 */
type_real compute_jacobian(const type_real xxi, const type_real zxi,
                           const type_real xgamma, const type_real zgamma);

/**
 * @brief compute jacobian at a particular point
 *
 * @param s_coorg scratch view of coorg subviewed at required element
 * @param ngnod Total number of control nodes per element
 * @param xi xi value of the point
 * @param gamma gamma value of point
 * @return type_real computed jacobian
 */
type_real compute_jacobian(const specfem::HostTeam::member_type &teamMember,
                           const specfem::HostScratchView2d<type_real> s_coorg,
                           const int ngnod, const type_real xi,
                           const type_real gamma);

/**
 * @brief compute jacobian at a particular point using derivatives of shape
 * function
 *
 * @param s_coorg scratch view of coorg subviewed at required element
 * @param ngnod Total number of control nodes per element
 * @param dershape2D derivative of shape function matrix calculated at (xi,
 * gamma)
 * @return type_real computed jacobian
 */
type_real compute_jacobian(const specfem::HostTeam::member_type &teamMember,
                           const specfem::HostScratchView2d<type_real> s_coorg,
                           const int ngnod,
                           const specfem::HostView2d<type_real> dershape2D);

// HostArray2d compute_partial_derivatives(const HostArray1d greekcoord,
//                                         const HostArray2d coorg,
//                                         const int ngod);
// double jacobian::compute_jacobian(const HostArray2d partial_der);
// double compute_jacobian(const HostArray1d greekcoord, const HostArray2d
// coorg,
//                         const int ngod);

// HostArray2d compute_inverse_partial_derivatives(const HostArray1d greekcoord,
//                                                 const HostArray2d coorg,
//                                                 const int ngod);
} // namespace jacobian

#endif
