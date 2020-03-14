package cse222;

import java.util.ArrayList;

/**
 * Branch class for cargo company.
 * @author Abdullah_Celik_171044002
 */
public class Branch
{
    private CargoCompany company;
    private int branchCode;
    private ArrayList<BranchEmployee> branchEmployee;
    private ArrayList<Shipment> shipment;

    /**
     * Constructor for  the branch with its company and branch code.
     * @param company branch's company.
     * @param branchCode branch's unique branch code.
     */
    public Branch(CargoCompany company, int branchCode)
    {
        this.company = company;
        setBranchCode(branchCode);
        branchEmployee = new ArrayList<>();
        shipment = new ArrayList<>();
    }

    /**
     * Getter function for the company that the branch belongs to.
     * @return the company the branch belongs to.
     */
    public CargoCompany getCompany() { return company; }

    /**
     * Getter function for the branch's branch employees.
     * @return the branch's branch employees.
     */
    public ArrayList<BranchEmployee> getBranchEmployee() { return branchEmployee; }

    /**
     * Getter function for the branch's shipments.
     * @return the branch's shipments.
     */
    public ArrayList<Shipment> getShipment() { return shipment; }

    /**
     * Getter function for the branch's unique branch code.
     * @return the branch's branch code.
     */
    public int getBranchCode() { return branchCode; }

    /**
     * Setter function for the branch's unique branch code.
     * @param branchCode is the new branch code for the branch.
     */
    public void setBranchCode(int branchCode) { this.branchCode = branchCode; }

    /**
     * Check whether the branch and other branch are same.
     * @param o other branch to compare them.
     * @return true if companies and branch code are same. Otherwise returns false.
     */
    @Override
    public boolean equals(Object o)
    {
        // javadoc
        if(o == null)
            return false;
        if(!(o instanceof Branch))
            return false;

        return getCompany().equals(((Branch)o).getCompany()) && getBranchCode() == ((Branch)o).getBranchCode();
    }

    /**
     * Create string representation of the branch.
     * @return string representation of the branch.
     */
    @Override
    public String toString() { return String.format("%s --> %d",getCompany().getCompanyName(),getBranchCode()); }
}