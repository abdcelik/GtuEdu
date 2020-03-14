package cse222.hw1;

/**
 * Branch employee interface for cargo company.
 * @author Abdullah_Celik_171044002
 */
public interface CompanyBranchEmployee
{
    boolean addUser(String name, String surname, int id);
    boolean removeUser(String name, String surname, int id);
    boolean enterShipmentInformation(int trackingNumber, Person sender, Person receiver);
    boolean removeShipmentInformation(int trackingNumber);
    boolean updateShipmentInformation(int trackingNumber,Status status);
}