<script>
    let imgSrc = $state(
        "https://placehold.co/150x100/0000FF/FFFFFF?text=old.jpg",
    );
</script>

<main
    class="min-h-auto rounded-xl text-black mt-5 bg-gray-100 p-6 font-sans space-y-6 max-w-3xl mx-auto"
>
    <!-- 🔹 EXERCISE 2 -->
    <section class="bg-white p-5 rounded-lg shadow-md">
        <h2 class="text-xl font-semibold mb-3 text-gray-700">
            Ex 2: Change Image `src`
        </h2>
        <img
            src={imgSrc}
            alt="Dynamic changing"
            class="border-2 border-gray-300 rounded mb-3 w-40"
        />
        <br />
        <button
            onclick={() =>
                (imgSrc =
                    "https://placehold.co/150x100/FF0000/FFFFFF?text=pqr.jpg")}
            class="bg-green-600 text-white px-4 py-2 rounded hover:bg-green-700 transition"
        >
            Change to opr.jpg
        </button>
    </section>
</main>
