package cse222;

/**
 * Administrator class for cargo company. Implement CompanyAdministrator.
 * @author Abdullah_Celik_171044002
 */
public class Administrator extends Person implements CompanyAdministrator
{
    private CargoCompany company;

    /**
     * Constructor for the administrator with name,surname,id and its company.
     * @param company of the administrator.
     * @param name of the administrator.
     * @param surname of the administrator.
     * @param id of the administrator.
     */
    public Administrator(CargoCompany company, String name, String surname, int id)
    {
        super(name,surname,id);
        this.company = company;
    }

    /**
     * Getter function for administrator's company variable.
     * @return administrator's company.
     */
    public CargoCompany getCompany() { return company; }

    /**
     * Add new branch for its company.
     * @param branchCode is the unique code for the branch.
     * @return true if the company does not have that branch. Otherwise returns false and adding operation is not successful.
     */
    public boolean addBranch(int branchCode)
    {
        Branch branch = new Branch(getCompany(),branchCode);

        if(getCompany().getBranch().contains(branch))
            return false;

        return getCompany().getBranch().add(branch);
    }

    /**
     * Remove the existing branch.
     * @param branchCode is the target branch to remove.
     * @return true if the company already has that branch. Otherwise return false and removing operation is not successful.
     */
    public boolean removeBranch(int branchCode)
    {
        return getCompany().getBranch().remove(new Branch(getCompany(),branchCode));
    }

    /**
     * Add new branch employee to a branch.
     * @param branchCode the target branch to add a new branch employee.
     * @param name of the branch employee.
     * @param surname of the branch employee.
     * @param id of the branch employee.
     * @return true if the branch doesn't have that branch employee. Otherwise returns false and adding branch employee operation is not successful.
     */
    public boolean addBranchEmployee(int branchCode, String name, String surname, int id)
    {
        int index;

        if((index = getCompany().getBranch().indexOf(new Branch(getCompany(),branchCode))) == -1)
            return false;

        BranchEmployee branchEmployee = new BranchEmployee(getCompany().getBranch().get(index),name,surname,id);

        if(getCompany().getBranch().get(index).getBranchEmployee().contains(branchEmployee))
            return false;

        return getCompany().getBranch().get(index).getBranchEmployee().add(branchEmployee);
    }

    /**
     * Remove the existing branch employee from a branch.
     * @param branchCode the target branch to remove the current branch employee.
     * @param name of the branch employee.
     * @param surname of the branch employee.
     * @param id of the branch employee.
     * @return true if the branch employee is removed. Otherwise returns false.
     */
    public boolean removeBranchEmployee(int branchCode, String name, String surname, int id)
    {
        int index;

        if((index = getCompany().getBranch().indexOf(new Branch(getCompany(),branchCode))) == -1)
            return false;

        return getCompany().getBranch().get(index).getBranchEmployee().remove(new BranchEmployee(getCompany().getBranch().get(index),name,surname,id));
    }

    /**
     * Add new transportation personnel to the company.
     * @param name of the transportation personnel.
     * @param surname of the transportation personnel.
     * @param id of the transportation personnel.
     * @return true if the company does not have that person and operation is successful. Otherwise returns false.
     */
    public boolean addTransportationPersonnel(String name, String surname, int id)
    {
        TransportationPersonnel transportationPersonnel = new TransportationPersonnel(getCompany(),name,surname,id);

        if(getCompany().getTransportationPersonnel().contains(transportationPersonnel))
            return false;

        return getCompany().getTransportationPersonnel().add(transportationPersonnel);
    }

    /**
     * Remove the existing transportation personnel from the company.
     * @param name of the transportation personnel.
     * @param surname of the transportation personnel.
     * @param id of the transportation personnel.
     * @return true if the company already has that person and operation is successful. Otherwise return false.
     */
    public boolean removeTransportationPersonnel(String name, String surname, int id)
    {
        return getCompany().getTransportationPersonnel().remove(new TransportationPersonnel(getCompany(),name,surname,id));
    }

    /**
     * Check whether administrator and other administrator are same company,name,surname and id.
     * @param o other person to compare this person.
     * @return true if they are equals. Otherwise returns false.
     */
    @Override
    public boolean equals(Object o)
    {
        if(o == null)
            return false;
        if(!(o instanceof Administrator))
            return false;

        return  getCompany().equals(((Administrator)o).getCompany()) && super.equals(o);
    }

    /**
     * Create a string representation of the administrator.
     * @return a string representation of the administrator.
     */
    @Override
    public String toString() { return "Company : " + getCompany().getCompanyName() + "\n" + super.toString(); }
}