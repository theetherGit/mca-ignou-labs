<script>
    let headingColor = $state("red");
</script>

<main
    class="min-h-auto rounded-xl text-black mt-5 bg-gray-100 p-6 font-sans space-y-6 max-w-3xl mx-auto"
>
    <section class="bg-white p-5 rounded-lg shadow-md">
        <h2 class="text-xl font-semibold mb-3 text-gray-700">
            Ex 3: Change H2 Color
        </h2>
        <h2 style="color: {headingColor};" class="text-2xl font-bold mb-3">
            Click button to change my color
        </h2>
        <button
            onclick={() => (headingColor = "green")}
            class="bg-purple-600 text-white px-4 py-2 rounded hover:bg-purple-700 transition"
        >
            Change Color
        </button>
    </section>
</main>
