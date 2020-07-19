/**
 * For a class that implements the binary search three.
 * @param <E> the parameter of generic type
 */
public interface SearchTree<E>
{
    /**
     * Inserts item where it belongs in the tree.
     * @param item the object to be inserted
     * @return true if item is inserted. Otherwise returns false
     */
    boolean add(E item);

    /**
     * Returns true if the target is found in the tree.
     * @param target the object to te searched
     * @return true if the target is found in the tree. Otherwise returns false
     */
    boolean contains(E target);

    /**
     * Returns a reference to the data in the node that is equal to target.
     * @param target the object to be searched
     * @return a reference to the data in the node that is equal to target. If no such node is found, returns null
     */
    E find(E target);

    /**
     * Removes target(if found) from tree and returns it.
     * @param target the object to be deleted
     * @return target if found from tree. Otherwise returns null
     */
    E delete(E target);

    /**
     * Removes target(if found) from tree and returns true.
     * @param target the object to be removed
     * @return true if found from tree. Otherwise return false
     */
    boolean remove(E target);
}
