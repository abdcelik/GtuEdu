package cse222.hw1;

/**
 * TransportationPersonnel class for cargo company. Extends Person. Implements CompanyTransportationPersonnel
 * @author Abdullah_Celik_171044002
 */
public class TransportationPersonnel extends Person implements CompanyTransportationPersonnel
{
    private CargoCompany company;

    /**
     * Constructor for the transportation personnel with its company,name,surname and id.
     * @param company its belongs to.
     * @param name transportation personnel's name.
     * @param surname transportation personnel's surname.
     * @param id transportation personnel's id.
     */
    public TransportationPersonnel(CargoCompany company, String name, String surname, int id)
    {
        super(name,surname,id);
        this.company = company;
    }

    /**
     * Getter function for transportation personnel's company it belongs to.
     * @return the company it belongs to.
     */
    public CargoCompany getCompany() { return company; }

    /**
     * Update the shipment status.
     * @param trackingNumber of the shipment.
     * @return true if the operation is successful. Otherwise returns false.
     */
    public boolean updateShipment(int trackingNumber)
    {
        Shipment ship = null;

        if((ship = getCompany().queryShipment(trackingNumber)) == null)
            return false;

        ship.setStatus(Status.DELIVERED);
        return true;
    }

    /**
     * Check whether the current person and the other person are the same or not.
     * @param o other person to compare this person.
     * @return true if the current person and other person are same company,name,surname and id. Otherwise returns false.
     */
    @Override
    public boolean equals(Object o)
    {
        if(o == null)
            return false;
        if(!(o instanceof TransportationPersonnel))
            return false;

        return getCompany().equals(((TransportationPersonnel)o).getCompany()) && super.equals(o);
    }

    /**
     * Create a string representation of the transportation personnel.
     * @return a string representation of the transportation personnel.
     */
    @Override
    public String toString() { return  "Company Name: " + getCompany().getCompanyName() + "\n" + super.toString(); }
}