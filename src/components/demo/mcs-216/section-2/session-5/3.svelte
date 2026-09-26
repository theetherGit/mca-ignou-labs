<script lang="ts">
    let inputVal = $state("");
    let displayVal = $state("");

    function handleUpper(e: Event) {
        const target = e.target as HTMLInputElement;
        inputVal = target.value.toUpperCase();
        displayVal = inputVal;
    }
</script>

<div class="p-8 bg-gray-50 min-h-auto text-black mt-5 rounded-xl">
    <h2 class="text-xl font-semibold mb-4 text-gray-800">
        Exercise 3: Auto Uppercase
    </h2>

    <input
        type="text"
        value={inputVal}
        onchange={handleUpper}
        placeholder="Type & press Enter or blur..."
        class="w-full max-w-md p-3 border border-gray-300 rounded focus:outline-blue-500 focus:ring-2 focus:ring-blue-200"
    />

    <p class="mt-4 text-lg font-medium text-gray-700">
        Converted: {displayVal || "Waiting for input..."}
    </p>
</div>
