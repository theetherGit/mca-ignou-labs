<script>
    // Reactive array simulating DOM child nodes
    let products = $state([
        { id: "laptop", label: "💻 Laptop: $1,200" },
        { id: "cellphone", label: "📱 Cell Phone: $800" },
    ]);

    function addTV() {
        products.push({ id: "tv", label: "📺 TV: $1,500" });
    }

    function deleteCellPhone() {
        products = products.filter((p) => p.id !== "cellphone");
    }
</script>

<div
    class="max-w-2xl mx-auto p-6 bg-gray-50 min-h-auto text-black rounded-xl mt-5"
>
    <h2 class="text-xl font-semibold mb-4 text-gray-800">Product Details</h2>

    <div class="space-y-2 mb-4">
        {#each products as product}
            <p class="bg-white p-3 rounded shadow-sm border border-gray-200">
                {product.label}
            </p>
        {/each}
    </div>

    <div class="flex gap-3">
        <button
            onclick={addTV}
            class="px-4 py-2 bg-green-600 text-white rounded hover:bg-green-700 transition"
        >
            Add TV
        </button>
        <button
            onclick={deleteCellPhone}
            class="px-4 py-2 bg-red-600 text-white rounded hover:bg-red-700 transition"
        >
            Delete Cell Phone
        </button>
    </div>
</div>
