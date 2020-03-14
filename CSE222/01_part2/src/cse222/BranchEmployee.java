package cse222;

/**
 * Branch Employee class for cargo company. Extends Person. Implements CompanyBranchEmployee.
 * @author Abdullah_Celik_171044002
 */
public class BranchEmployee extends Person implements CompanyBranchEmployee
{
    private Branch branch;

    /**
     * Constructor for the branch employee with its branch,name,surname and id.
     * @param branch to which the branch employee belongs.
     * @param name branch employee's name.
     * @param surname branch employee's surname.
     * @param id branch employee's id.
     */
    public BranchEmployee(Branch branch, String name, String surname, int id)
    {
        super(name,surname,id);
        this.branch = branch;
    }

    /**
     * Getter function for the branch to which branch employee belongs.
     * @return branch to which the branch employee belongs.
     */
    public Branch getBranch() { return branch; }

    /**
     * Add new user to company.
     * @param name of the user.
     * @param surname of the user.
     * @param id of the user.
     * @return true if the company does not have that user and adding operation is successful. Otherwise returns false.
     */
    public boolean addUser(String name, String surname, int id)
    {
        Person person = new Person(name,surname,id);

        if(getBranch().getCompany().getCustomer().contains(person))
            return false;

        return getBranch().getCompany().getCustomer().add(person);
    }

    /**
     * Remove the existing user from the company.
     * @param name of the user.
     * @param surname of the user.
     * @param id of the user.
     * @return true if the company already has that user and removing operation is successful. Otherwise return false.
     */
    public boolean removeUser(String name, String surname, int id)
    {
        return getBranch().getCompany().getCustomer().remove(new Person(name,surname,id));
    }

    /**
     * Enter a new shipment.
     * @param trackingNumber of the shipment.
     * @param sender the person who sent the cargo.
     * @param receiver the person who received the cargo.
     * @return true if the operation is successful. Otherwise returns false.
     */
    public boolean enterShipmentInformation(int trackingNumber, Person sender, Person receiver)
    {
        Shipment ship = new Shipment(trackingNumber,sender,receiver,Status.ATBRANCH);

        if(getBranch().getShipment().contains(ship))
            return false;

        return getBranch().getShipment().add(ship);
    }

    /**
     * Remove the existing shipment.
     * @param trackingNumber of the target shipment.
     * @return true if the operation is successful. Otherwise returns false.
     */
    public boolean removeShipmentInformation(int trackingNumber)
    {
        return getBranch().getShipment().remove(new Shipment(trackingNumber,null,null,null));
    }

    /**
     * Update the existing shipment.
     * @param trackingNumber of the shipment
     * @param status of the shipment
     * @return true if operation is successful. Otherwise returns false.
     */
    public boolean updateShipmentInformation(int trackingNumber,Status status)
    {
        Shipment ship = getBranch().getCompany().queryShipment(trackingNumber);

        if(ship == null)
            return false;

        ship.setStatus(status);
        return true;
    }

    /**
     * Check whether the current person and other person are the same branch,name,surname and id.
     * @param o other object to compare this person.
     * @return true if the branches,names,surnames and ids are the same.
     */
    @Override
    public boolean equals(Object o)
    {
        if(o == null)
            return false;
        if(!(o instanceof BranchEmployee))
            return false;

        return getBranch().equals(((BranchEmployee)o).getBranch()) && super.equals(o);
    }

    /**
     * Create a string representation of the branch employee.
     * @return a string representation of the branch employee.
     */
    @Override
    public String toString()
    {
        return  "Company Name: " + getBranch().getCompany().getCompanyName() + "\n" +
                "Branch Code: " + getBranch().getBranchCode() + "\n" +
                super.toString();
    }
}