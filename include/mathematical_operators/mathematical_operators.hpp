#ifndef _MATHEMATICAL_OPERATORS_HPP
#define _MATHEMATICAL_OPERATORS_HPP

#include "kokkos_abstractions.h"
#include "specfem_setup.hpp"
#include <Kokkos_Core.hpp>

namespace specfem {
namespace mathematical_operators {

/**
 * @brief Compute gradients of a 2D field within a spectral element
 *
 * This function is to used inside a team policy. It computes gradients of 2D
 * field where is field has X and Z dimension, for example displacement field in
 * Elastic domains.
 *
 * @todo Add example to how to use this function
 *
 * @param team_member Team handle to team policy of the calling team
 * @param ispec spectral element number
 * @param xix inverted partial derivates \f$\partial \xi / \partial x\f$
 * @param xiz inverted partial derivates \f$\partial \xi / \partial z\f$
 * @param gammax inverted partial derivates \f$\partial \gamma / \partial
 * x\f$
 * @param gammaz inverted partial derivates \f$\partial \gamma / \partial
 * z\f$
 * @param s_hprime_xx Derivatives of quadrature polynomials at quadrature
 * points in X-dimension at every quadrature point within the ispec element.
 * @param s_hprime_zz Derivatives of quadrature polynomials at quadrature
 * points in Z-dimension at every quadrature point within the ispec element.
 * @param field_x X component of field at every quadrature point within the
 * ispec element
 * @param field_z Z component of field at every quadrature point within the
 * ispec element
 * @param s_duxdx \f$\partial u_x / \partial x\f$  component of field at
 * every quadrature point within the ispec element
 * @param s_duxdz \f$\partial u_x / \partial z\f$  component of field at
 * every quadrature point within the ispec element
 * @param s_duzdx \f$\partial u_z / \partial x\f$ component of field at
 * every quadrature point within the ispec element
 * @param s_duzdz \f$\partial u_z / \partial z\f$ component of field at
 * every quadrature point within the ispec element
 */
KOKKOS_FUNCTION void compute_gradients_2D(
    const specfem::kokkos::DeviceTeam::member_type &team_member,
    const int ispec, const specfem::kokkos::DeviceView3d<type_real> xix,
    const specfem::kokkos::DeviceView3d<type_real> xiz,
    const specfem::kokkos::DeviceView3d<type_real> gammax,
    const specfem::kokkos::DeviceView3d<type_real> gammaz,
    const specfem::kokkos::DeviceScratchView2d<type_real> s_hprime_xx,
    const specfem::kokkos::DeviceScratchView2d<type_real> s_hprime_zz,
    const specfem::kokkos::DeviceScratchView2d<type_real> field_x,
    const specfem::kokkos::DeviceScratchView2d<type_real> field_z,
    specfem::kokkos::DeviceScratchView2d<type_real> s_duxdx,
    specfem::kokkos::DeviceScratchView2d<type_real> s_duxdz,
    specfem::kokkos::DeviceScratchView2d<type_real> s_duzdx,
    specfem::kokkos::DeviceScratchView2d<type_real> s_duzdz);

/**
 * @brief Compute gradients of a 2D field within a spectral element
 *
 * This function is to used inside a team policy. It computes gradients of 2D
 * field where is field has X and Z dimension, for example displacement field in
 * Elastic domains.
 *
 * @todo Add example to how to use this function
 * @note This is specialized kernel when NGLL is known at compile time and NGLLX
 * == NGLLZ. This is significantly faster ~10X faster than the kernel where NGLL
 * is defined at runtime.
 *
 * @param team_member Team handle to team policy of the calling team
 * @param ispec spectral element number
 * @param xix inverted partial derivates \f$\partial \xi / \partial x\f$
 * @param xiz inverted partial derivates \f$\partial \xi / \partial z\f$
 * @param gammax inverted partial derivates \f$\partial \gamma / \partial
 * x\f$
 * @param gammaz inverted partial derivates \f$\partial \gamma / \partial
 * z\f$
 * @param s_hprime_xx Derivatives of quadrature polynomials at quadrature
 * points in X-dimension at every quadrature point within the ispec element.
 * @param s_hprime_zz Derivatives of quadrature polynomials at quadrature
 * points in Z-dimension at every quadrature point within the ispec element.
 * @param field_x X component of field at every quadrature point within the
 * ispec element
 * @param field_z Z component of field at every quadrature point within the
 * ispec element
 * @param s_duxdx \f$\partial u_x / \partial x\f$  component of field at
 * every quadrature point within the ispec element
 * @param s_duxdz \f$\partial u_x / \partial z\f$  component of field at
 * every quadrature point within the ispec element
 * @param s_duzdx \f$\partial u_z / \partial x\f$ component of field at
 * every quadrature point within the ispec element
 * @param s_duzdz \f$\partial u_z / \partial z\f$ component of field at
 * every quadrature point within the ispec element
 */
template <int NGLL>
KOKKOS_FUNCTION void compute_gradients_2D(
    const int &xz, const int &ispec,
    const specfem::kokkos::DeviceView3d<type_real> xix,
    const specfem::kokkos::DeviceView3d<type_real> xiz,
    const specfem::kokkos::DeviceView3d<type_real> gammax,
    const specfem::kokkos::DeviceView3d<type_real> gammaz,
    const specfem::kokkos::StaticDeviceScratchView2d<type_real, NGLL, NGLL>
        s_hprime_xx,
    const specfem::kokkos::StaticDeviceScratchView2d<type_real, NGLL, NGLL>
        s_hprime_zz,
    const specfem::kokkos::StaticDeviceScratchView2d<type_real, NGLL, NGLL>
        field_x,
    const specfem::kokkos::StaticDeviceScratchView2d<type_real, NGLL, NGLL>
        field_z,
    type_real &duxdxl, type_real &duxdzl, type_real &duzdxl, type_real &duzdzl);

/**
 * @brief Compute and contributions of stress integrands in 2D.
 *
 * This function is to used inside a team policy. It computes gradients the
 * integrals given stress integrands and add them to second derivative of field.
 *
 * @param team_member Team handle to team policy of the calling team
 * @param wxgll Quadrature weights in X-dimension
 * @param wzgll Quadrature weights in Z-dimension
 * @param s_hprimewgll_xx `s_hprimewgll_xx(iz, ix) = hprime_xx(iz, ix)
 * wxgll(iz)` where h_primexx is the derivative of quadrature polynomials at
 * quadrature points in X-dimension at every quadrature point within the ispec
 * element.
 * @param s_hprimewgll_zz `s_hprimewgll_zz(iz, ix) = hprime_zz(iz, ix)
 * wzgll(iz)` where h_primexx is the derivative of quadrature polynomials at
 * quadrature points in Z-dimension at every quadrature point within the ispec
 * element.
 * @param s_iglob 2 dimensional ScratchView used to store global numbering
 * for every quadrature point within the ispec element
 * @param stress_integrand_1 value of jacobian * (sigma_xx * xix +
 * sigma_xz * xiz) evaluated at every quadrature point within the ispec
 * element
 * @param stress_integrand_2 value of `jacobian * (sigma_xz * xix +
 * sigma_zz * xiz)` evaluated at every quadrature point within the ispec
 * element
 * @param stress_integrand_3 value of `jacobian * (sigma_xx * gammax +
 * sigma_xz * gammaz)` evaluated at every quadrature point within the
 * ispec element
 * @param stress_integrand_4 value of `jacobian * (sigma_xz * gammax +
 * sigma_zz * gammaz)` evaluated at every quadrature point within the
 * ispec element
 * @param field_dot_dot Second derivative of field to update
 */
KOKKOS_FUNCTION void add_contributions(
    const specfem::kokkos::DeviceTeam::member_type &team_member,
    const specfem::kokkos::DeviceView1d<type_real> wxgll,
    const specfem::kokkos::DeviceView1d<type_real> wzgll,
    const specfem::kokkos::DeviceScratchView2d<type_real> s_hprimewgll_xx,
    const specfem::kokkos::DeviceScratchView2d<type_real> s_hprimewgll_zz,
    const specfem::kokkos::DeviceScratchView2d<int> s_iglob,
    const specfem::kokkos::DeviceScratchView2d<type_real> stress_integrand_1,
    const specfem::kokkos::DeviceScratchView2d<type_real> stress_integrand_2,
    const specfem::kokkos::DeviceScratchView2d<type_real> stress_integrand_3,
    const specfem::kokkos::DeviceScratchView2d<type_real> stress_integrand_4,
    specfem::kokkos::DeviceView2d<type_real, Kokkos::LayoutLeft> field_dot_dot);

/**
 * @brief Compute and contributions of stress integrands in 2D.
 *
 * This function is to used inside a team policy. It computes gradients the
 * integrals given stress integrands and add them to second derivative of field.
 *
 * @note This is specialized kernel when NGLL is known at compile time and NGLLX
 * == NGLLZ. This is significantly faster ~10X faster than the kernel where NGLL
 * is defined at runtime.
 *
 * @tparam Number of quadrature points in X and Z dimensions
 * @param team_member Team handle to team policy of the calling team
 * @param wxgll Quadrature weights in X-dimension
 * @param wzgll Quadrature weights in Z-dimension
 * @param s_hprimewgll_xx `s_hprimewgll_xx(iz, ix) = hprime_xx(iz, ix)
 * wxgll(iz)` where h_primexx is the derivative of quadrature
 * polynomials at quadrature points in X-dimension at every quadrature point
 * within the ispec element.
 * @param s_hprimewgll_zz `s_hprimewgll_zz(iz, ix) = hprime_zz(iz, ix)
 * wzgll(iz)` where h_primexx is the derivative of quadrature
 * polynomials at quadrature points in Z-dimension at every quadrature point
 * within the ispec element.
 * @param s_iglob 2 dimensional ScratchView used to store global numbering
 * for every quadrature point within the ispec element
 * @param stress_integrand_1 value of `jacobian * (sigma_xx * xix +
 * sigma_xz * xiz)` evaluated at every quadrature point within the ispec
 * element
 * @param stress_integrand_2 value of `jacobian * (sigma_xz * xix +
 * sigma_zz * xiz)` evaluated at every quadrature point within the ispec
 * element
 * @param stress_integrand_3 value of `jacobian * (sigma_xx * gammax +
 * sigma_xz * gammaz)` evaluated at every quadrature point within the
 * ispec element
 * @param stress_integrand_4 value of `jacobian * (sigma_xz * gammax +
 * sigma_zz * gammaz)` evaluated at every quadrature point within the
 * ispec element
 * @param field_dot_dot Second derivative of field to update
 */
template <int NGLL>
KOKKOS_FUNCTION void add_contributions(
    const specfem::kokkos::DeviceTeam::member_type &team_member,
    const specfem::kokkos::DeviceView1d<type_real> wxgll,
    const specfem::kokkos::DeviceView1d<type_real> wzgll,
    const specfem::kokkos::StaticDeviceScratchView2d<type_real, NGLL, NGLL>
        s_hprimewgll_xx,
    const specfem::kokkos::StaticDeviceScratchView2d<type_real, NGLL, NGLL>
        s_hprimewgll_zz,
    const specfem::kokkos::StaticDeviceScratchView2d<int, NGLL, NGLL> s_iglob,
    const specfem::kokkos::StaticDeviceScratchView2d<type_real, NGLL, NGLL>
        stress_integrand_1,
    const specfem::kokkos::StaticDeviceScratchView2d<type_real, NGLL, NGLL>
        stress_integrand_2,
    const specfem::kokkos::StaticDeviceScratchView2d<type_real, NGLL, NGLL>
        stress_integrand_3,
    const specfem::kokkos::StaticDeviceScratchView2d<type_real, NGLL, NGLL>
        stress_integrand_4,
    specfem::kokkos::DeviceView2d<type_real, Kokkos::LayoutLeft> field_dot_dot);
} // namespace mathematical_operators
} // namespace specfem

#endif
