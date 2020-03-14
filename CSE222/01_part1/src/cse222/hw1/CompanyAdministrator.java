package cse222.hw1;

/**
 * Administrator interface for cargo company.
 * @author Abdullah_Celik_171044002
 */
public interface CompanyAdministrator
{
    boolean addBranch(int branchCode);
    boolean removeBranch(int branchCode);

    boolean addBranchEmployee(int branchCode, String name, String surname, int id);
    boolean removeBranchEmployee(int branchCode, String name, String surname, int id);

    boolean addTransportationPersonnel(String name, String surname, int id);
    boolean removeTransportationPersonnel(String name, String surname, int id);
}