<script lang="ts">
    let a = $state(""),
        b = $state(""),
        output = $state("");

    function calculate() {
        try {
            const numA = parseFloat(a),
                numB = parseFloat(b);
            if (isNaN(numA) || isNaN(numB))
                throw new TypeError("Invalid input");
            if (numB === 0) throw new RangeError("Division by zero");
            output = `✅ Result: ${numA / numB}`;
        } catch (err) {
            const error = err instanceof Error ? err : new Error(String(err));
            output = `❌ Error (${error.name}): ${error.message}`;
        }
    }
</script>

<div
    class="p-8 bg-gray-50 min-h-auto mt-5 rounded-xl text-black flex items-center justify-center"
>
    <div class="bg-white p-6 rounded-xl shadow-lg w-full max-w-md">
        <h2 class="text-xl font-semibold mb-4 text-gray-800">Divide a / b</h2>
        <input
            bind:value={a}
            type="number"
            placeholder="Number a"
            class="w-full p-3 border border-gray-300 rounded mb-3 focus:outline-blue-500"
        />
        <input
            bind:value={b}
            type="number"
            placeholder="Number b"
            class="w-full p-3 border border-gray-300 rounded mb-4 focus:outline-blue-500"
        />

        <button
            onclick={calculate}
            class="w-full bg-blue-600 text-white py-3 rounded-lg hover:bg-blue-700 transition font-medium"
        >
            Calculate
        </button>

        <p class="mt-4 text-lg font-medium text-gray-700 min-h-6">
            {output || "Waiting for input..."}
        </p>
    </div>
</div>
