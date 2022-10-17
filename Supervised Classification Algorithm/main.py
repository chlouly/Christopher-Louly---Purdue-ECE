import numpy as np

from sklearn.neighbors import KNeighborsClassifier
from sklearn import svm
from sklearn.neural_network import MLPClassifier

# Import scikit-learn metrics module for accuracy calculation
from sklearn import metrics

from utils import load_MNIST


def get_KNN_results(train_data, train_labels, test_data, test_labels, k):
    """
    args:
    train_Data : 5000x784 numpy array of MNIST training images
    train_labels : corresponding 5000 ground truth labels
    test_Data : 1000x784 numpy array of MNIST test images
    test_labels : corresponding 1000 ground truth labels
    k : input argument for sklearn.neighbors.KNeighborsClassifier

    Returns: Accuracy and confusion matrix
    """
    knn = KNeighborsClassifier(n_neighbors=k)

    knn.fit(train_data, train_labels)

    test_pred = knn.predict(test_data)

    accuracy = metrics.accuracy_score(test_labels, test_pred)

    confusion_matrix = metrics.confusion_matrix(
        test_labels, test_pred
    )

    return accuracy, confusion_matrix


def get_SVM_results(train_data, train_labels, test_data, test_labels):
    """
    args:
    train_Data : 5000x784 numpy array of MNIST training images
    train_labels : corresponding 5000 ground truth labels
    test_Data : 1000x784 numpy array of MNIST test images
    test_labels : corresponding 1000 ground truth labels
    Returns: Accuracy and confusion matrix
    """
    svm_classifier = svm.LinearSVC(random_state=1)

    svm_classifier.fit(train_data, train_labels)

    test_pred = svm_classifier.predict(test_data)

    accuracy = metrics.accuracy_score(test_labels, test_pred)

    confusion_matrix = metrics.confusion_matrix(
        test_labels, test_pred
    )

    return accuracy, confusion_matrix


def get_MLP_results(train_data, train_labels, test_data, test_labels):
    """
    args:
    train_Data : 5000x784 numpy array of MNIST training images
    train_labels : corresponding 5000 ground truth labels
    test_Data : 1000x784 numpy array of MNIST test images
    test_labels : corresponding 1000 ground truth labels
    Returns: Accuracy and confusion matrix
    """
    mlp = MLPClassifier(hidden_layer_sizes=(15,10), random_state=1, activation="relu")
    
    mlp.fit(train_data, train_labels)

    test_pred = mlp.predict(test_data)

    accuracy = metrics.accuracy_score(test_labels, test_pred)

    confusion_matrix = metrics.confusion_matrix(
        test_labels, test_pred
    )

    return accuracy, confusion_matrix


if __name__ == "__main__":
    train_data, train_labels, test_data, test_labels = load_MNIST()

    for k in range(1, 6):
        print(str(k) + "-neighbors result:")
        accuracy, confusion_matrix = get_KNN_results(
            train_data, train_labels, test_data, test_labels, k
        )
        print("Accuracy:", accuracy)
        print(confusion_matrix)
        print()

    print("SVM Result")
    accuracy, confusion_matrix = get_SVM_results(
        train_data, train_labels, test_data, test_labels
    )
    print("Accuracy:", accuracy)
    print(confusion_matrix)
    print()

    print("MLP Result")
    accuracy, confusion_matrix = get_MLP_results(
        train_data, train_labels, test_data, test_labels
    )
    print("Accuracy:", accuracy)
    print(confusion_matrix)
    print()
