import pennylane as qml
import numpy as np

# Create a quantum device with 1 qubit using the default simulator
dev = qml.device("default.qubit", wires=1)

@qml.qnode(dev)
def circuit():
    qml.Hadamard(wires=0)  # Apply Hadamard gate
    return qml.expval(qml.PauliZ(0))  # Measure expectation value of Pauli-Z

# Run the circuit
result = circuit()
print(f"Result of quantum circuit: {result}")
