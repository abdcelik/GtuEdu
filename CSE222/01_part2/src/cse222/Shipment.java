package cse222;

/**
 * Shipment class for cargo company.
 * @author Abdullah_Celik_171044002
 */
public class Shipment
{
    private int trackingNumber;
    private Person sender;
    private Person receiver;
    private Status status;

    /**
     * Constructor for the shipment with tracking number, sender, receiver and status.
     * @param trackingNumber of the shipment.
     * @param sender of the shipment.
     * @param receiver of the shipment.
     * @param status of the shipment.
     */
    public Shipment(int trackingNumber, Person sender, Person receiver, Status status)
    {
        setTrackingNumber(trackingNumber);
        setSender(sender);
        setReceiver(receiver);
        setStatus(status);
    }

    /**
     * Getter function for the shipment's tracking number.
     * @return tracking number of the shipment.
     */
    public int getTrackingNumber() { return trackingNumber; }

    /**
     * Getter function for the shipment's sender.
     * @return sender of the shipment.
     */
    public Person getSender() { return sender; }

    /**
     * Getter function for the shipment's receiver.
     * @return receiver of the shipment.
     */
    public Person getReceiver() { return receiver; }

    /**
     * Getter function for the shipment's status.
     * @return status of the shipment.
     */
    public Status getStatus() { return status; }

    /**
     * Setter function for the shipment's tracking number.
     * @param trackingNumber new tracking number.
     */
    public void setTrackingNumber(int trackingNumber) { this.trackingNumber = trackingNumber; }

    /**
     * Setter function for the shipment's sender.
     * @param sender new sender.
     */
    public void setSender(Person sender) { this.sender = sender;}

    /**
     * Setter function for the shipment's receiver.
     * @param receiver new receiver.
     */
    public void setReceiver(Person receiver) { this.receiver = receiver;}

    /**
     * Setter function for the shipment's status.
     * @param status new status.
     */
    public void setStatus(Status status) { this.status = status; }

    /**
     * Check whether the current shipment and other are same or not.
     * @param o other object to compare them.
     * @return true if the current shipment and other are the same. Otherwise returns false.
     */
    @Override
    public boolean equals(Object o)
    {
        if(o == null)
            return false;
        if(!(o instanceof Shipment))
            return false;

        Shipment other = (Shipment)o;

        return getTrackingNumber() == other.getTrackingNumber();
    }

    /**
     * Create a string representation of the shipment.
     * @return a string representation of the shipment.
     */
    @Override
    public String toString()
    {
        return String.format("Tracking ID: %d\nSender Information\n%s\nReceiver Information\n%s\nStatus : %s",getTrackingNumber(),getSender(),getReceiver(),getStatus());
    }
}