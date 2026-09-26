<script>
    // Svelte 5 reactive state
    let firstName = $state("");
    let lastName = $state("");
    let fullName = $state("");
</script>

<main
    class="min-h-auto rounded-xl text-black mt-5 bg-gray-100 p-6 font-sans space-y-6 max-w-3xl mx-auto"
>
    <section class="bg-white p-5 rounded-lg shadow-md">
        <h2 class="text-xl font-semibold mb-3 text-gray-700">
            Ex 1: Concatenate Full Name
        </h2>
        <div class="flex gap-2 mb-3">
            <input
                type="text"
                bind:value={firstName}
                placeholder="First Name"
                class="border border-gray-300 px-3 py-2 rounded flex-1 focus:outline-blue-500"
            />
            <input
                type="text"
                bind:value={lastName}
                placeholder="Last Name"
                class="border border-gray-300 px-3 py-2 rounded flex-1 focus:outline-blue-500"
            />
        </div>
        <button
            onclick={() => (fullName = `${firstName} ${lastName}`)}
            class="bg-blue-600 text-white px-4 py-2 rounded hover:bg-blue-700 transition"
        >
            Try
        </button>
        {#if fullName}
            <p class="mt-3 font-bold text-gray-800">Full Name: {fullName}</p>
        {/if}
    </section>
</main>
