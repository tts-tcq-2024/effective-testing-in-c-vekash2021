#include <stdio.h>
#include <assert.h>

int alertFailureCount = 0;

int networkAlertStub(float celcius) {
    printf("ALERT: Temperature is %.1f celcius.\n", celcius);
    // Return 200 for ok
    // Return 500 for not-ok
    // stub always succeeds and returns 200
    return 200;
}

void alertInCelcius(float farenheit) {
    float celcius = (farenheit - 32) * 5 / 9;
    int returnCode = networkAlertStub(celcius);
    if (returnCode != 200) {
        // non-ok response is not an error! Issues happen in life!
        // let us keep a count of failures to report
        // However, this code doesn't count failures!
        // Add a test below to catch this bug. Alter the stub above, if needed.
        alertFailureCount += 0;
    }
}

void testAlertInCelcius() {
    // Reset failure count before test
    alertFailureCount = 0;

    // Test Case 1: Normal Temperature (Should not fail)
    alertInCelcius(100.0); // 100°F -> 37.78°C (normal temperature)
    assert(alertFailureCount == 0); // No failures should be recorded

    // Test Case 2: High Temperature (Should fail)
    alertInCelcius(500.0); // 500°F -> 260°C (high temperature, should cause failure)
    assert(alertFailureCount == 1); // One failure should be recorded

    // Test Case 3: Extremely High Temperature (Should fail)
    alertInCelcius(1000.0); // 1000°F -> 537.78°C (extremely high, should cause another failure)
    assert(alertFailureCount == 2); // Two failures should be recorded

    // Test Case 4: Low Temperature (Should not fail)
    alertInCelcius(-40.0); // -40°F -> -40°C (low temperature, no failure)
    assert(alertFailureCount == 2); // Still two failures, as this should not add to failure count
}


int main() {
    // alertInCelcius(400.5);
    // alertInCelcius(303.6);
    // alertInCelcius(504.6);
    // alertInCelcius(104.6);
    testAlertInCelcius();
    printf("%d alerts failed.\n", alertFailureCount);
    printf("All is well (maybe!)\n");
    return 0;
}
