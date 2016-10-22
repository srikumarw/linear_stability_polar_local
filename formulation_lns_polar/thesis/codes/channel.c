/* ***************************************************** *
 * This program is a illustration for using the biglobal *
 * stability code 					 *
 * ***************************************************** */
static char help[] = "Helf Yourself!";
#include <stdio.h>
#include <math.h>
#include <slepceps.h>
#include <data.h>

int read_base_flow(ndr_data_t *);
#undef __FUNCT__
#define __FUNCTI__ "main"
int main(int argc, char **args)
{
    int z;
    ndr_data_t ndrdata;
    PetscErrorCode ierr;
    PetscScalar beta, omega;
    PetscMPIInt rank,size;
    PetscScalar *test;
    co_trnfm_t *tr;

    ndrdata.nx = 40;
    ndrdata.ny = 40;
    ndrdata.re = 1000;
    ndrdata.pr = 1.0;
    ndrdata.gamma = 1.4;
    beta = 1.0;

    SlepcInitialize(&argc,&args,(char*)0,help);
    ierr = MPI_Comm_rank(PETSC_COMM_WORLD,&rank);
    ierr = MPI_Comm_size(PETSC_COMM_WORLD,&size);

    tr = (co_trnfm_t *) malloc(sizeof(co_trnfm_t));
    ndrdata.trnfm = tr;

    ///////// Read base flow /////////
    read_base_flow(&ndrdata);

    ///////// Initialise jacobian elements /////////
    cheb_jacobian(&ndrdata);

    ///////// Set up dispersion relation /////////
    lns_biglobal_temporal(1,&beta,&omega,&ndrdata);
    set_bc_temporal(&ndrdata);
    
    ///////// Solve the eigenvalue problem /////////
    eigen_solver(&ndrdata);

    ierr = SlepcFinalize(); CHKERRQ(ierr);

    return 0;
}

int read_base_flow(ndr_data_t *arg)
{

    /* **************************************** *
     * Write your function to update ndr_data_t *
     * with base flow variables                 *
     * **************************************** */

    return 0;
}



