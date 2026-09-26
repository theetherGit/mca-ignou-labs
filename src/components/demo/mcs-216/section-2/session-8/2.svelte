<script lang="ts">
    import { fade } from "svelte/transition";

    // Lab Requirement: Object literal with methods
    const product = {
        id: "P1001",
        name: "Wireless Mechanical Keyboard",
        description: "RGB backlit, USB-C charging, Blue switches",
        price: 149.99,
        CalculateDisc: function (percentage: number) {
            return this.price - this.price * (percentage / 100);
        },
        displayProductDetails: function (percentage: number) {
            return {
                name: this.name,
                description: this.description,
                original: this.price,
                discounted: this.CalculateDisc(percentage),
            };
        },
    };

    let discountInput = $state("");
    let result: ReturnType<typeof product.displayProductDetails> | null =
        $state(null);

    function calculate() {
        const percent = parseFloat(discountInput) || 0;
        result = product.displayProductDetails(percent);
    }
</script>

<div
    class="p-8 bg-gray-50 min-h-auto text-black mt-5 rounded-xl flex flex-col items-center justify-center gap-6"
>
    <h2 class="text-2xl font-bold text-gray-800">
        Product Discount Calculator
    </h2>

    <div class="bg-white p-6 rounded-xl shadow-md w-full max-w-md space-y-4">
        <div>
            <label
                for="discountInput"
                class="block text-sm font-medium text-gray-700 mb-1"
                >Discount %</label
            >
            <input
                bind:value={discountInput}
                type="number"
                placeholder="e.g., 20"
                class="w-full p-3 border border-gray-300 rounded-lg focus:outline-blue-500 focus:ring-2 focus:ring-blue-200"
            />
        </div>

        <button
            onclick={calculate}
            class="w-full py-3 bg-green-600 text-white rounded-lg hover:bg-green-700 transition font-medium shadow"
        >
            Calculate & Display Details
        </button>

        {#if result}
            <div
                transition:fade
                class="mt-4 bg-gray-50 p-4 rounded-lg space-y-2 border border-gray-200"
            >
                <p>
                    <span class="font-semibold text-gray-700">📦 Name:</span>
                    {result.name}
                </p>
                <p>
                    <span class="font-semibold text-gray-700"
                        >📝 Description:</span
                    >
                    {result.description}
                </p>
                <p>
                    <span class="font-semibold text-gray-700">💰 Original:</span
                    >
                    ${result.original.toFixed(2)}
                </p>
                <p class="text-lg font-bold text-green-700 mt-2">
                    🏷️ Discounted: ${result.discounted.toFixed(2)}
                </p>
            </div>
        {/if}
    </div>
</div>
